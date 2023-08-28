from flask import request
from flask_jwt_extended import get_jwt_identity, jwt_required
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector

# @@ 매칭 포스팅 작성
class MatchPostingResource(Resource) :
    @jwt_required()
    def post(self, team_id) :
        
        # {
        #     "title" : "machtest4",
        #     "content" : "machtest1"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into matchPosting
                    (userId, teamId, title, content)
                    values
                    (%s, %s, %s, %s);'''

            record = (user_id, team_id, data['title'], data['content'])

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
            connection.commit()

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()
            return {"error" : str(e)}, 503

        return {'result' : 'success'}



# @@ 모든 매칭 포스팅 가져오기
class MatchPostingListResource(Resource) :
    def get(self) :
        # 쿼리 스트링으로 오는 데이터는 아래처럼 처리해준다.
        # request.args는 딕셔너리다

        # request.arg 코드작성 방식1
        offset = request.args.get('offset')
        limit = request.args.get('limit')

        # request.arg 코드작성 방식2
        # offset = request.args['offset']
        # limit = request.args['limit']

        # 예외처리로 에러코드 보내주기
        if offset is None or limit is None :
            return {'error' : '쿼리스트링 셋팅해 주세요',
                    'error_no' : 123}, 400
        
        try :
            # 데이터 업데이트
            connection = get_connection()

            query = '''select *
                    from matchPosting
                    limit '''+offset+''', '''+limit+''';'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 커서를 이용해서 쿼리문을 실행한다.
            cursor.execute(query,)

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
            'count' : len(result_list),
            "items" : result_list }, 200



# @@ 내가 쓴 매칭 포스팅 가져오기
class MatchPostingMyListResource(Resource) :
    @jwt_required()
    def get(self) :
        
        # 쿼리 스트링으로 오는 데이터는 아래처럼 처리해준다.
        # request.args는 딕셔너리다

        # request.arg 코드작성 방식1
        offset = request.args.get('offset')
        limit = request.args.get('limit')

        # request.arg 코드작성 방식2
        # offset = request.args['offset']
        # limit = request.args['limit']

        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

    
        # 예외처리로 에러코드 보내주기
        if offset is None or limit is None :
            return {'error' : '쿼리스트링 셋팅해 주세요',
                    'error_no' : 123}, 400
    
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from matchPosting
                    where userId = %s
                    limit '''+offset+''', '''+limit+''';'''

            record = (user_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 커서를 이용해서 쿼리문을 실행한다.
            cursor.execute(query, record)

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
            'count' : len(result_list),
            "items" : result_list }, 200



# @@ 내가 쓴 매칭 포스팅 수정
class MatchPostingInfoResource(Resource) :
    def put(self, matchposting_id) :
        
        # {
        #     "title": "matchrecive1",
        #     "content": "matchtest1"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''update matchPosting
                    set title = %s,
                    content = %s
                    where id = %s'''

            record = (data['title'], data['content'], matchposting_id)

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 5. 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
            connection.commit()

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()
            return {"error" : str(e)}, 503

        return {'result' : 'success'}



    # @@ 내가 쓴 매칭 포스팅 삭제
    def delete(self, matchposting_id) :
        try :

            # DB에 연결
            connection = get_connection()

            # 2. 쿼리문 만들기
            query = '''delete from matchPosting
                    where Id = %s;'''

            record = (matchposting_id, )

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



# @@ 매칭 포스팅에 댓글 작성
class MatchRepleResource(Resource) :
    @jwt_required()
    def post(self, matchposting_id) :
        
        # {
        #     "content": "matchreple1"
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into matchReple
                    (userId, matchPostingId, content)
                    values
                    (%s, %s, %s);'''

            record = (user_id, matchposting_id, data['content'])

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
            connection.commit()

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()
            return {"error" : str(e)}, 503

        return {'result' : 'success'}



    # @@ 매칭 포스팅의 댓글 가져오기
    def get(self, matchposting_id) :
    
        # 쿼리 스트링으로 오는 데이터는 아래처럼 처리해준다.
        # request.args는 딕셔너리다

        # request.arg 코드작성 방식1
        offset = request.args.get('offset')
        limit = request.args.get('limit')

        # request.arg 코드작성 방식2
        # offset = request.args['offset']
        # limit = request.args['limit']

        # 예외처리로 에러코드 보내주기
        if offset is None or limit is None :
            return {'error' : '쿼리스트링 셋팅해 주세요',
                    'error_no' : 123}, 400

        # 디비로부터 리스트를 가져온다.
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from matchReple
                    where matchpostingId = %s
                    limit '''+offset+''', '''+limit+''';'''

            record = (matchposting_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 커서를 이용해서 쿼리문을 실행한다.
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

            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            'count' : len(result_list),
            "items" : result_list }, 200
