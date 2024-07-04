from flask import request
from flask_jwt_extended import create_access_token, get_jwt, jwt_required
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector
from email_validator import validate_email, EmailNotValidError
from utils import check_password, hash_password



# @@ 회원가입
class UserRegisterResource(Resource) :
    def post(self) :

        # {
        #     "email": "test1@gmail.com",
        #     "password": "test1234",
        #     "subEmail" : "test4@gmail.com",
        #     "question": "앱의 이름은?",
        #     "questionAn": "매치런",
        #     "name": "testName1",
        #     "nickname": "testNick1",
        #     "address": "...api",
        #     "addrDetail": "...api"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        # 이메일 형식 체크
        try :
            validate_email( data['email'] )
        except EmailNotValidError as e:
            return {'error' : str(e), 'error_no' : 1} , 400

        # 비밀번호 길이 체크
        # 4자리 이상, 12자리 이하가 정상!
        # error_no => 분류해서 저장
        if len(data['password']) < 4 or len(data['password']) > 12 :
            return {'error' : '비번 길이확인하세요', 'error_no' : 2}, 400

        # 비밀번호를 암호화
        hashed_password = hash_password( data['password'] )

        # 데이터베이스에 회원정보를 저장한다
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into user
                    (email, password, subEmail, question, questionAn, name,
                     nickName, address, addrDetail)
                    values
                    ( %s, %s, %s, %s, %s, %s, %s, %s, %s);'''

            record = (data['email'], 
                      hashed_password,
                      data['subEmail'],
                      data['question'],
                      data['questionAn'],
                      data['name'],
                      data['nickName'],
                      data['address'],
                      data['addrDetail'])

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
            connection.commit()

            # 디비에 저장된 아이디값 가져오기
            user_id = cursor.lastrowid

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()
            return {"error" : str(e), 'error_no' : 3}, 503

        # 6. JWT억세스 토큰을 생성해서, 클라이언트에 응답해준다.
        
        # user_id 를 바로 보내면 안되고,
        # JWT 로 암호화 해서 보내준다.
        # 암호화 하는 방법
        access_token = create_access_token(user_id)
                        # 로그인 토큰 만료하는 시간설정
                        # expires_delta=datetime.timedelta(minutes=1))

        return {'result' : 'success', 'access_token' : access_token }, 200


# @@ 로그인
class UserLoginResource(Resource) :
    def post(self) :

        # {
        #     "email": "abc@gmail.com",
        #     "password": "1234"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        # 이 이메일로, 데이터베이스에서 셀렉트 한다.
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from user
                    where email = %s;'''

            record = (data['email'], )

            # 커서를 가져온다. select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()
            # print(result_list)

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e)}, 503

        # 이 이메일의 유저가 없으면, 클라이언트에
        # 이 이메일은 회원이 아니라고 응답해준다.
        if len(result_list) == 0 :
            return {'error' : '회원가입 정보가 없습니다.',
                    'error_no' : 6}, 400

        # 비밀번호가 맞는지 확인한다.
        # DB에 저장되어있는 유저 정보!
        user_info = result_list[0]

        check = check_password(data['password'], user_info['password'])

        if check == False :
            return {'error' : '비밀번호가 맞지 않습니다.',
                    'error_no' : 7}, 400

        # JWT 억세스 토큰 생성해서 리턴해준다.
        access_token = create_access_token( user_info['id'] )

        return {'result' : 'success',
                'access_token' : access_token}, 200



# @@ 로그아웃
jwt_blacklist = set()
class UserLogoutResource(Resource) :
    @jwt_required()
    def post(self) :

        jti = get_jwt()['jti']
        print(jti)

        jwt_blacklist.add(jti)

        return {'result' : 'success'}, 200



# @@ 아이디 찾기
class UserIdSearchResource(Resource) :
    def get(self) :

        # {
        #     "name": "testName2",
        #     "subEmail": "test44@gmail.com",
        #     "question": "앱의 이름은?",
        #     "questionAn": "매치런"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        try :

            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select email
                    from user
                    where name = %s
                    and subEmail = %s 
                    and question = %s
                    and questionAn = %s;'''

            record = (data['name'], data['subEmail'], data['question'], data['questionAn'])

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # print(result_list)

            # 자원해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            "items" : result_list }, 200



# @@ 비밀번호 찾기
class UserPasswordSearchResource(Resource) :
    def get(self) :

        # {
        #     "email": "test4@gmail.com",
        #     "question": "앱의 이름은?",
        #     "questionAn": "매치런"
        # }
        
        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from user
                    where email = %s 
                    and question = %s
                    and questionAn = %s;'''

            record = (data['email'], data['question'], data['questionAn'])

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # print(result_list)

            # 중요! 디비에서 가져온 timestamp 난
            # 파이썬의 datetime 으로 자동 변경된다.
            # json은 datetime 같은게 없다 그냥 문자열이다
            # 문제는! 이 데이터를 json 으로 바로 보낼 수 없으므로,
            # 문자열로 바꿔서 다시 저장해서 보낸다.
            i = 0
            for record in result_list :
                result_list[i]['createdAt'] = record['createdAt'].isoformat()
                result_list[i]['updatedAt'] = record['updatedAt'].isoformat()
                i = i + 1

            # 자원해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            "items" : result_list }, 200


# @@ 비밀번호 재설정
class UserPasswordResetResource(Resource) :
    def put(self, user_id) :
        
        # {
        #     "password" : "recive1234"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        # 비밀번호 길이 체크
        # 4자리 이상, 12자리 이하가 정상!
        if len(data['password']) < 4 or len(data['password']) > 12 :
            return {'error' : '비번 길이확인하세요', 'error_no' : 2}, 400

        # 비밀번호를 암호화
        hashed_password = hash_password( data['password'] )

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''update user
                    set password = %s
                    where id = %s;'''

            record = (hashed_password, user_id )

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야한다
            connection.commit()

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e)}, 503
        
        
        return {'result' : 'success'}, 200



# @@ 이메일 중복확인
class UserEmailUniqueResource(Resource) :
    def get(self) :    
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select email
                    from user;'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 실행
            cursor.execute(query,)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # 자원해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            "items" : result_list }, 200



# @@ 닉네임 중복확인
class UserNicknameUniqueResource(Resource) :
    def get(self) :    
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select nickName
                    from user;'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query,)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # 자원해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            "items" : result_list }, 200
