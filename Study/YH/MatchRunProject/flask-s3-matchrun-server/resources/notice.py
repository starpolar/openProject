from flask import request
from flask_jwt_extended import jwt_required, get_jwt_identity
from flask_restful import Resource
from config import Config
from mysql_connection import get_connection
import mysql.connector
import datetime
import boto3


# @@ 공지사항 작성
class NoticeListResource(Resource) :
    @jwt_required()
    def post(self, team_id) :

        # 클라이언트로부터 데이터를 받아온다.
        user_id = get_jwt_identity()

        # 이미지 없을때 처리
        if 'noticeImg' not in request.files :

            title = request.form['title']
            content = request.form['content']

            try :
                # DB에 연결
                connection = get_connection()
                
                # 쿼리문 만들기
                query = '''insert into notice
                        (userId, teamId, title, content)
                        values
                        (%s, %s, %s, %s);'''

                record = (user_id, team_id, title, content)

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

            file = request.files['noticeImg']
            title = request.form['title']
            content = request.form['content']

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
                query = '''insert into notice
                        (userId, teamId, imgUrl, title, content)
                        values
                        (%s, %s, %s, %s, %s);'''

                record = (user_id, team_id, new_file_name, title, content)

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



    # @@ 공지사항 가져오기
    def get(self, team_id) :
        
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from notice
                    where teamId = %s;'''

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



# @@ 공지사항 수정
class NoticeApplyResource(Resource) :
    def put(self, notice_id) :

        # 이미지 없을때 처리
        if 'noticeImg' not in request.files :

            try :
                # DB에 연결
                connection = get_connection()

                # 쿼리문 만들기
                query = '''select *
                        from notice
                        where id = %s;'''

                record = (notice_id, )

                # select 문은, dictionary = True 를 해준다.
                cursor = connection.cursor(dictionary = True)

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record )

                # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                result_list = cursor.fetchall()

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

                title = request.form['title']
                content = request.form['content']

                # 쿼리문 만들기
                query ='''update notice
                    set title = %s,
                    content = %s,
                    imgUrl = null
                    where id = %s'''

                record = (title, content, notice_id)

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
                # 데이터 업데이트
                connection = get_connection()

                query = '''select *
                        from notice
                        where id = %s;'''

                record = (notice_id, )

                # select 문은, dictionary = True 를 해준다.
                cursor = connection.cursor(dictionary = True)

                # 쿼리문을 커서를 이용해서 실행한다
                cursor.execute(query, record )

                # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
                result_list = cursor.fetchall()

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

                file = request.files['noticeImg']
                title = request.form['title']
                content = request.form['content']

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

                s3 = boto3.client('s3',aws_access_key_id = Config.ACCESS_KEY, aws_secret_access_key = Config.SECRET_ACCESS)

                try :
                    s3.upload_fileobj(file,
                                    Config.S3_BUCKET,
                                    file.filename,
                                    ExtraArgs = {'ACL' : 'public-read', 'ContentType':file.content_type})
                except Exception as e :
                    return {'error' : str(e)}, 500

                # 쿼리문 만들기
                query ='''update notice
                    set title = %s,
                    content = %s,
                    imgUrl = %s
                    where id = %s'''

                record = (title, content, new_file_name, notice_id)

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

    # @@ 공지사항 삭제
    def delete(self, notice_id) :
        try :

            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from notice
                    where id = %s;'''

            record = (notice_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

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
            query = '''delete from notice
                    where Id = %s;'''

            record = (notice_id, )

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
