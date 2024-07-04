from flask import request
from flask_jwt_extended import jwt_required, get_jwt_identity
from flask_restful import Resource
from config import Config
from mysql_connection import get_connection
import mysql.connector
import datetime
import boto3

# @@ 쪽지보내기
class LetterApplyResource(Resource) :
    @jwt_required()
    def post(self) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        data = request.get_json() 

        # 데이터베이스에 팀정보 인서트한다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select * 
                    from user
                    where nickName = %s;'''

            record = (data['nickName'], )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            if result_list == [] :
                return {"error" : "noNickName"}

            receive_user_id = result_list[0]['id']

            if receive_user_id == user_id :
                return {"error" : "sameUser"}

            # 쿼리문 만들기
            query = '''insert into letter
                    (sendUserId, receiveUserId, content)
                    values
                    (%s, %s, %s);'''
            
            record = (user_id,  receive_user_id, data['content'])

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

    # @@ 내가 받은 쪽지 가져오기
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

        # 페이징처리 예외처리
        if offset is None or limit is None :
            return {'error' : '쿼리스트링 셋팅해 주세요',
                    'error_no' : 123}, 400
        
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select l.sendUserId, l.content, l.createdAt
                    from letter l
                    where receiveUserId = %s;
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
                # result_list[i]['updatedAt'] = record['updatedAt'].isoformat()
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