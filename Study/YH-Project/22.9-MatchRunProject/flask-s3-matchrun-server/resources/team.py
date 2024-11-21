from flask import request
from flask_jwt_extended import jwt_required, get_jwt_identity
from flask_restful import Resource
from config import Config
from mysql_connection import get_connection
import mysql.connector
import datetime
import boto3



# @@ 팀 생성 api (이미지 유무 ok)
class TeamListResource(Resource) :
    @jwt_required()
    def post(self) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 이미지 없을때 처리
        if 'logoImg' not in request.files :

            name = request.form['name']
            sports = request.form['sports']
            introduce = request.form['introduce']
            address = request.form['address']
            addrDetail = request.form['addrDetail']

            try :
                # DB 연결
                connection = get_connection()

                # file = request.files['noticeImg']
                # title = request.form['title']
                # content = request.form['content']
                
                # 쿼리문 만들기
                query = '''insert into team
                        (userId, name, sports, introduce,
                        address, addrDetail)
                        values
                        (%s, %s, %s, %s, %s, %s);'''

                record = (user_id, name, sports, introduce, address, addrDetail)

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

        # 이미지 있을때 처리
        else :
                
            file = request.files['logoImg']
            name = request.form['name']
            sports = request.form['sports']
            introduce = request.form['introduce']
            address = request.form['address']
            addrDetail = request.form['addrDetail']

            # S3 에 파일 업로드
            # 파일명을 우리가 변경해 준다.
            # 파일명은, 유니크하게 만들어야 한다
            current_time = datetime.datetime.now()
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
                s3.upload_fileobj(file, Config.S3_BUCKET, file.filename, ExtraArgs = {'ACL' : 'public-read', 'ContentType':file.content_type})

            except Exception as e :
                return {'error' : str(e)}, 500

            # DB에 저장
            try :
                # DB에 연결
                connection = get_connection()

                # file = request.files['logoImg']
                # name = request.form['name']
                # sports = request.form['sports']
                # introduce = request.form['introduce']
                # address = request.form['address']
                # addrDetail = request.form['addrDetail']
                
                # 쿼리문 만들기
                query = '''insert into team
                        (userId, imgUrl, name, sports, introduce,
                        address, addrDetail)
                        values
                        (%s, %s, %s, %s, %s, %s, %s);'''

                record = (user_id, new_file_name, name, sports, introduce, address, addrDetail)

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



    # @@ 내가 속한 팀 정보 가져오기
    @jwt_required()
    def get(self) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 디비로부터 데이터를 받아서 ,클라이언트에 보내준다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select t.*
                    from teamFollow tf
                    join team t
                    on tf.teamId = t.id
                    where tf.userId = %s
                    group by tf.id;'''

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



# @@ 팀 상세정보 가져오기
class TeamInfoResource(Resource) :
    def get(self, team_id) :
        
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from team
                    where id = %s;'''

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


    # @@ 팀 정보 수정 api (+s3 삭제)
    @jwt_required()
    def put(self, team_id) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 이미지 없을때 처리
        if 'logoImg' not in request.files :

            try :
                # DB 연결
                connection = get_connection()
                
                # 쿼리문 만들기
                query = '''select * from team
                        where Id = %s and userId = %s;'''
                record = (team_id, user_id )

                # select 문은, dictionary = True 를 해준다.
                cursor = connection.cursor(dictionary = True)

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record)

                # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                result_list = cursor.fetchall()

                if result_list == [] :
                    return {'result' : 'not my team'}, 200

                imgUrl = result_list[0]['imgUrl']

                if imgUrl is not None :

                    session = boto3.Session(aws_access_key_id=Config.ACCESS_KEY,
                        aws_secret_access_key=Config.SECRET_ACCESS)

                    # s3_client = session.client('s3')
                    s3_resource = session.resource('s3')
                    my_bucket = s3_resource.Bucket(Config.S3_BUCKET)

                    response = my_bucket.delete_objects(
                        Delete={
                            'Objects': [
                                {
                                    'Key': imgUrl   # the_name of_your_file
                                }
                            ]
                        }
                    )

                name = request.form['name']
                sports = request.form['sports']
                introduce = request.form['introduce']
                address = request.form['address']
                addrDetail = request.form['addrDetail']

                # 쿼리문 만들기
                query = '''update team
                        set name = %s,
                        sports = %s,
                        introduce = %s,
                        address = %s,
                        addrDetail = %s,
                        imgUrl = null
                        where id = %s and userId = %s'''

                record = (name, sports, introduce, address, addrDetail, team_id, user_id)

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

        # 이미지 있을때 처리
        else :

            try :
                # DB 연결
                connection = get_connection()

                # 쿼리문 만들기
                query = '''select * from team
                        where Id = %s and userId = %s;'''

                record = (team_id, user_id )

                # select 문은, dictionary = True 를 해준다.
                cursor = connection.cursor(dictionary = True)

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record )

                # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                result_list = cursor.fetchall()

                if result_list == [] :
                    return {'result' : 'not my team'}, 200

                imgUrl = result_list[0]['imgUrl']

                if imgUrl is not None :

                    session = boto3.Session(aws_access_key_id=Config.ACCESS_KEY, aws_secret_access_key=Config.SECRET_ACCESS)

                    # s3_client = session.client('s3')
                    s3_resource = session.resource('s3')
                    my_bucket = s3_resource.Bucket(Config.S3_BUCKET)

                    response = my_bucket.delete_objects(
                        Delete={
                            'Objects': [
                                {
                                    'Key': imgUrl   # the_name of_your_file
                                }
                            ]
                        }
                    )

                file = request.files['logoImg']
                name = request.form['name']
                sports = request.form['sports']
                introduce = request.form['introduce']
                address = request.form['address']
                addrDetail = request.form['addrDetail']

                # S3 에 파일 업로드
                # 파일명을 우리가 변경해 준다.
                # 파일명은, 유니크하게 만들어야 한다
                current_time = datetime.datetime.now()
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
                    s3.upload_fileobj(file, Config.S3_BUCKET, file.filename, ExtraArgs = {'ACL' : 'public-read', 'ContentType':file.content_type})

                except Exception as e :
                    return {'error' : str(e)}, 500

                # 쿼리문 만들기
                query = '''update team
                        set name = %s,
                        sports = %s,
                        introduce = %s,
                        address = %s,
                        addrDetail = %s,
                        imgUrl = %s
                        where id = %s and userId = %s'''

                record = (name, sports, introduce, address, addrDetail, new_file_name, team_id, user_id)

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



# @@ 팀 삭제 (관리자만 ok) api (+s3 삭제)
    @jwt_required()
    def delete(self, team_id) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select * from team
                    where Id = %s and userId = %s;'''

            record = ( team_id, user_id )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # print(result_list)

            if result_list == [] :
                return {'result' : 'no admin'}, 200
            
            else :
                
                imgUrl = result_list[0]['imgUrl']

                if imgUrl is not None :

                    session = boto3.Session(aws_access_key_id=Config.ACCESS_KEY, aws_secret_access_key=Config.SECRET_ACCESS)

                    # s3_client = session.client('s3')
                    s3_resource = session.resource('s3')
                    my_bucket = s3_resource.Bucket(Config.S3_BUCKET)

                    response = my_bucket.delete_objects(
                        Delete={
                            'Objects': [
                                {
                                    'Key': imgUrl   # the_name of_your_file
                                }
                            ]
                        }
                    )

                # 쿼리문 만들기
                query = '''delete from team
                        where Id = %s and userId = %s;'''

                record = ( team_id, user_id )

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



# @@ 팀의 인원의 정보 가져오기(+인원수)
class TeamFollowInfoResource(Resource) :
    def get(self, team_id) :
        
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select u.imgUrl as profile, u.nickName, tf.id as teamFollowId
                    from teamFollow tf
                    join user u
                    on tf.userId = u.id
                    where tf.teamId = %s;'''

            record = (team_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record )

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

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            'count' : len(result_list),
            "items" : result_list }, 200



# @@ 팀 탈퇴
class TeamFollowDeleteResource(Resource) :
    def delete(self, teamfollow_id) :

        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from teamFollow
                    where Id = %s;'''

            record = ( teamfollow_id, )

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



# @@ 팀의 리뷰의 평균값 가져오기
class TeamReviewAvgResource(Resource) :
    def get(self, team_id) :
        
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select avg(mannerRating) as mannerAvg,
                    avg(skillRating) as skillAvg
                    from matchReview
                    where matchRevieweeTeamId = %s;'''

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
                # result_list[i]['createdAt'] = record['createdAt'].isoformat()
                # result_list[i]['updatedAt'] = record['updatedAt'].isoformat()
                result_list[i]['mannerAvg'] = float(record['mannerAvg'])
                result_list[i]['skillAvg'] = float(record['skillAvg'])
                i = i + 1

            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" ,
            "items" : result_list }, 200

