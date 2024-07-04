from flask import request
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector


# 체육시설 찾기
class SportsCenterResource(Resource) :
    def get(self) :
        # 클라이언트로부터 데이터를 받아온다.
        keyword = request.args['keyword']
        offset = request.args['offset']
        limit = request.args['limit']

        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from sportsCenter
                    where name like '%'''+keyword+'''%' 
                    limit '''+offset+''', '''+limit+''';'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query,)

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

