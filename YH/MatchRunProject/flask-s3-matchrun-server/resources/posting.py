from flask import request
from flask_jwt_extended import get_jwt_identity, jwt_required
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector
from datetime import datetime
import boto3
from config import Config
import requests


# @@ 포스팅 작성 (+번역된 결과 태그로 저장)
class PostingTeamResource(Resource) :
    @jwt_required()
    def post(self, team_id) :

        # 유저토큰으로 부터 user_id 반환
        user_id = get_jwt_identity()

        if 'photo' not in request.files :
            return {'error' : '파일을 업로드하세요'}, 400

        file = request.files['photo']
        content = request.form['content']

        # S3 에 파일 업로드
        # 파일명을 우리가 변경해 준다.
        # 파일명은, 유니크하게 만들어야 한다
        current_time = datetime.now()
        new_file_name = current_time.isoformat().replace(':', '_') + '.jpg'

        # 유저가 올린 파일의 이름을, 내가 만든 파일명으로 변경
        file.filename = new_file_name

        # S3 에 업로드 하면 된다.
        # S3는 AWS꺼니 AWS에서 어떻게해서 올려라 할것이니 라이브러리가 있겠지?
        # AWS 의 라이브러리를 사용해야 한다.
        # 이 파이썬 라이브러리가 boto3 라이브러리다!
        # boto3 라이브러리 설치
        # pip install boto3

        s3 = boto3.client('s3', aws_access_key_id = Config.ACCESS_KEY, aws_secret_access_key = Config.SECRET_ACCESS)

        try :
            s3.upload_fileobj(file,
                            Config.S3_BUCKET,
                            file.filename,
                            ExtraArgs = {'ACL' : 'public-read', 'ContentType':file.content_type})
        except Exception as e :
            return {'error' : str(e)}, 500

        # DB에 저장
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into posting
                    (userId, content, imgUrl, teamId)
                    values
                    (%s, %s, %s, %s);'''

            record = (user_id, content, new_file_name, team_id)

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
            connection.commit()

            # 이 포스팅의 아이디값을 가져온다
            posting_id = cursor.lastrowid  

            # 자원 해제
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()
            return {"error" : str(e)}, 503

        # 오브젝트 디텍션을 수행해서, 레이블의 Name을 가져온다.
        client = boto3.client('rekognition', 'ap-northeast-2', aws_access_key_id=Config.ACCESS_KEY, aws_secret_access_key = Config.SECRET_ACCESS)
        response = client.detect_labels(Image={'S3Object' : {'Bucket' : Config.S3_BUCKET,'Name' : new_file_name }} , MaxLabels=10)

        # 레이블의 Name을 가지고, 태그를 만든다!!! 중요!!

        # label['Name'] 의 문자열을 tag_name 테이블에서 찾는다.
        # 테이블에 이 태그가 있으면, id 를 가져온다.
        # 이 태그 id와 위의 postingId 를 가지고,
        # tag 테이블에 저장한다.

        # 만약 tag_name 테이블에 이 태그가 없으면,
        # tag_name 테이블에, 이 태그이름을 저장하고,
        # 저장된 id 값과 위의 postingId 를 가지고,
        # tag 테이블에 저장한다.

        for label in response['Labels']:

            # 파파고로 태그이름 번역
            #---------------------------------------------------------------------------------
            text = label['Name']

            # 네이버 파파고 API 호출한다.
            headers = {'Content-Type' : 'application/x-www-form-urlencoded; charset=UTF-8',
                'X-Naver-Client-Id' : Config.NAVER_CLIENT_ID,
                'X-Naver-Client-Secret' : Config.NAVER_CLIENT_SECRET}

            data = {'source' : 'en',
                    'target' : 'ko',
                    'text' : text}

            res = requests.post(Config.NAVER_PAPAGO_URL, data, headers= headers)

            # print(res.json())
            # print(type(res.json()))
            
            res = res.json()
            # print(res['message']['result']['translatedText'])
            result_text = res['message']['result']['translatedText']
            #---------------------------------------------------------------------------------

            label['Name'] = result_text

            # label['Name'] 이 값을 우리는 태그 이름으로 사용할것.
            try :
                # DB 연결
                connection = get_connection()

                # 쿼리문 만들기
                query = '''select *
                        from tagName
                        where name = %s;'''
                
                record = (label['Name'], )

                # select 문은, dictionary = True 를 해준다.
                cursor = connection.cursor(dictionary = True)

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record)

                # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                result_list = cursor.fetchall()

                if len(result_list) == 0 :
                    # 태그이름을 insert 해준다
                    query = '''insert into tagName
                            (name)
                            values
                            (%s );'''
            
                    record = (label['Name'],  )

                    # 커서를 가져온다.
                    cursor = connection.cursor()

                    # 쿼리문을 커서를 이용해서 실행한다
                    cursor.execute(query, record)

                    # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
                    connection.commit()

                    # 디비에 저장된 아이디값 가져오기
                    tag_name_id = cursor.lastrowid
                else :
                    tag_name_id = result_list[0]['id']


                # posting_id 와 tag_name_id 가 준비되었으니
                # tag 테이블에 insert 한다
                
                # 쿼리문 만들기 (태그이름을 insert 해준다)
                query = '''insert into tag
                        (tagId, postingId)
                        values
                        ( %s, %s);'''

                record = (tag_name_id, posting_id )

                # 커서를 가져온다.
                cursor = connection.cursor()

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record)

                # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
                connection.commit()

                # 자원해제
                cursor.close()
                connection.close()

            except mysql.connector.Error as e :
                print(e)
                cursor.close()
                connection.close()

                return {"error" : str(e), 'error_no' : 20}, 503

        return {'result' : 'success'}



    # @@ 해당 팀 포스팅 가져오기
    def get(self, team_id) :
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
            # DB연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select p.*, u.nickName, count(l.postingId) as likesCnt
                    from posting p
                    join user u
                    on p.userId = u.id
                    left join likes l
                    on p.id = l.postingId
                    where p.teamId = %s
                    group by p.id
                    limit '''+offset+''', '''+limit+''';'''

            record = (team_id, )

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

            # 자원 해제
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


# @@ 내가 쓴 포스팅 가져오기
class PostingMyResource(Resource) :
    @jwt_required()
    def get(self) :
        
        # 유저토큰으로 부터 user_id 반환
        user_id = get_jwt_identity()

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
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select p.*, u.nickName, count(l.postingId) as likesCnt
                    from posting p
                    join user u
                    on p.userId = u.id
                    left join likes l
                    on p.id = l.postingId
                    where p.userId = %s
                    group by p.id
                    limit '''+offset+''', '''+limit+''';'''

            record = (user_id, )

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



# @@ 내가 쓴 포스팅 수정하기
class PostingInfoResource(Resource) :
    @jwt_required()
    def put(self, posting_id) :

        # photo(file), content(text)
        
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        if 'photo' not in request.files:
            # 쿼리 부분을 만든다.
            content = request.form['content']

            # S3에 파일 업로드가 필요 없으므로, 디비에 저장한다.
            try :
                # DB에 연결
                connection = get_connection()

                # 쿼리문 만들기
                query = '''update posting
                        set content = %s,
                        imgUrl = null 
                        where id = %s and userId = %s;'''
                
                record = (content, posting_id, user_id)

                # 커서를 가져온다.
                cursor = connection.cursor()

                # 쿼리문을 커서를 이용해서 실행한다.
                cursor.execute(query, record)

                # 커넥션을 커밋해줘야 한다 => 디비에 영구적으로 반영하라는 뜻
                connection.commit()

                # 자원 해제
                cursor.close()
                connection.close()

            except mysql.connector.Error as e :
                print(e)
                cursor.close()
                connection.close()
                return {'error' : str(e)}, 503

            return {'result' : 'success'}, 200

        else :
            # 쿼리 부분을 만든다.
            file = request.files['photo']
            content = request.form['content']

            # 파일이 있으니까, 파일명을 새로 만들어서
            # S3 에 업로드한다.

            # 2. S3 에 파일 업로드
            # 파일명을 우리가 변경해 준다.
            # 파일명은, 유니크하게 만들어야 한다.
            current_time = datetime.now()
            new_file_name = current_time.isoformat().replace(':', '_') + '.jpg'

            # 유저가 올린 파일의 이름을, 내가 만든 파일명으로 변경
            file.filename = new_file_name

            # S3 에 업로드 하면 된다.
            # AWS 의 라이브러리를 사용해야 한다.
            # 이 파이썬 라이브러리가 boto3 라이브러리다!
            # boto3 라이브러리 설치
            # pip install boto3 

            s3 = boto3.client('s3', 
                        aws_access_key_id = Config.ACCESS_KEY,
                        aws_secret_access_key = Config.SECRET_ACCESS)

            try :
                s3.upload_fileobj(file,
                                    Config.S3_BUCKET,
                                    file.filename,
                                    ExtraArgs = {'ACL':'public-read', 'ContentType':file.content_type} )                 

            except Exception as e :
                return {'error' : str(e)}, 500

            # 데이터 베이스에 업데이트 해준다.

            try :
                # DB에 연결
                connection = get_connection()

                # 쿼리문 만들기
                query = '''update posting
                        set content = %s , imgUrl = %s 
                        where id = %s and userId = %s;'''
                
                record = (content, new_file_name, posting_id, user_id)

                # 커서를 가져온다.
                cursor = connection.cursor()

                # 쿼리문을 커서를 이용해서 실행한다.
                cursor.execute(query, record)

                # 커넥션을 커밋해줘야 한다 => 디비에 영구적으로 반영하라는 뜻
                connection.commit()

                # 자원 해제
                cursor.close()
                connection.close()

            except mysql.connector.Error as e :
                print(e)
                cursor.close()
                connection.close()
                return {'error' : str(e)}, 503

            # aws rekognition 이용해서 labels 정보 가져오기
            # 오브젝트 디텍션을 수행해서, 레이블의 Name을 가져온다.
            client = boto3.client('rekognition', 'ap-northeast-2', aws_access_key_id=Config.ACCESS_KEY, aws_secret_access_key = Config.SECRET_ACCESS)
            response = client.detect_labels(Image={'S3Object' : {'Bucket' : Config.S3_BUCKET, 'Name' : new_file_name }}, MaxLabels=5)


            # 기존 태그를 삭제
            # 바뀐 태그 새로 저장
            #---------------------------------------------------------------------------------
            # 레이블의 Name을 가지고, 태그를 만든다!!! 중요!!

            # label['Name'] 의 문자열을 tag_name 테이블에서 찾는다.
            # 테이블에 이 태그가 있으면, id 를 가져온다.
            # 이 태그 id와 위의 postingId 를 가지고,
            # tag 테이블에 저장한다.

            # 만약 tag_name 테이블에 이 태그가 없으면,
            # tag_name 테이블에, 이 태그이름을 저장하고,
            # 저장된 id 값과 위의 postingId 를 가지고,
            # tag 테이블에 저장한다.
            #---------------------------------------------------------------------------------

            try :
                # DB에 연결
                connection = get_connection()

                # 삭제
                #---------------------------------------------------------------------------------
                query = '''delete from tag
                        where postingId = %s;'''

                record = (posting_id, )
                cursor = connection.cursor()
                cursor.execute(query, record)
                #---------------------------------------------------------------------------------

                for label in response['Labels']:
                    # label['Name'] 이 값을 우리는 태그 이름으로 사용할것.
                    query =  '''select *
                            from tagName
                            where name = %s;'''
                    
                    record = (label['Name'], )

                    # select 문은, dictionary = True 를 해준다.
                    cursor = connection.cursor(dictionary = True)

                    # 쿼리문을 커서를 이용해서 실행한다.
                    cursor.execute(query, record)

                    # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                    result_list = cursor.fetchall()

                    if len(result_list) == 0 :
                        # 태그이름을 insert 해준다
                        query = '''insert into tagName
                                (name)
                                values
                                (%s );'''
                
                        record = (label['Name'],  )

                        # 커서를 가져온다.
                        cursor = connection.cursor()

                        # 쿼리문을 커서를 이용해서 실행한다
                        cursor.execute(query, record)

                        # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
                        connection.commit()

                        # 디비에 저장된 아이디값 가져오기
                        tag_name_id = cursor.lastrowid
                    else :
                        tag_name_id = result_list[0]['id']


                    # posting_id 와 tag_name_id 가 준비되었으니
                    # tag 테이블에 insert 한다
                    
                    # 태그이름을 insert 해준다
                    query = '''insert into tag
                            (tagId, postingId)
                            values
                            ( %s, %s);'''

                    record = (tag_name_id, posting_id )

                    # 커서를 가져온다.
                    cursor = connection.cursor()

                    # 쿼리문을 커서를 이용해서 실행한다
                    cursor.execute(query, record)

                # 커넥션을 커밋해줘야한다 => 디비에 영구적으로 반영하는것
                connection.commit()

                cursor.close()
                connection.close()

            except mysql.connector.Error as e :
                print(e)
                cursor.close()
                connection.close()

                return {"error" : str(e), 'error_no' : 20}, 503


            return {'result' : 'success'}, 200
    


    # @@ 내가 쓴 포스팅 삭제하기
    @jwt_required()
    def delete(self, posting_id) :

        # 유저토큰으로 부터 user_id 반환
        user_id = get_jwt_identity()

        # 디비로부터 메모를 삭제한다
        # 내가 작성한 포스팅만 삭제 가능해야 한다.
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from posting
                    where id = %s and userId = %s;'''

            record = ( posting_id, user_id )

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            ### 여기서 유저아이디가 다르다면 except 로 이동해서 종료
            ### 조건문은 필요없음
            
            #---------------------------------------------------------------------------------

            # 쿼리문 만들기
            query = '''delete from likes
                    where postingId = %s;'''

            record = ( posting_id,)

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            #---------------------------------------------------------------------------------

            # 쿼리문 만들기
            query = '''delete from tag
                    where postingId = %s;'''

            record = ( posting_id,)

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            #---------------------------------------------------------------------------------
            
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



# @@ 포스팅에 좋아요
class PostingLikesResource(Resource) :
    @jwt_required()
    def post(self, posting_id) :

        # 유저토큰으로 부터 user_id 반환
        user_id = get_jwt_identity()

        # 받아온 데이터를 DB 저장
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into likes
                    (postingId, userId)
                    values
                    (%s, %s);'''

            record = (posting_id, user_id)

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야 한다 => 디비에 영구적으로 반영하라는 뜻
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
    


    # @@ 포스팅에 좋아요 취소
    @jwt_required()
    def delete(self, posting_id) :
               
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 디비로부터 메모를 삭제한다
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from likes
                    where postingId = %s and userId = %s;'''

            record = (posting_id, user_id )

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



# @@ 포스팅에 댓글 작성
class PostingRepleResource(Resource) :
    @jwt_required()
    def post(self, posting_id) :
        
        data = request.get_json()

        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 받아온 데이터를 DB 저장하면 된다.
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into postingReple
                    (postingId, userId, content)
                    values
                    (%s, %s, %s);'''

            record = (posting_id, user_id, data['content'])

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야 한다 => 디비에 영구적으로 반영하라는 뜻
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
    


    
    # @@ 포스팅에 댓글 가져오기
    def get(self, posting_id) :
    
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
            # 데이터 업데이트
            connection = get_connection()

            query = '''select *
                    from postingReple
                    where postingId = %s
                    limit '''+offset+''', '''+limit+''';'''

            record = (posting_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
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
            # 자원 해제
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



# @@ 포스팅에 댓글 삭제
class PostingRepleInfoResource(Resource) :
    def delete(self, reple_id) :
      
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from postingReple
                    where Id = %s;'''

            record = (reple_id, )

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
        