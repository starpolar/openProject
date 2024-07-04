from flask import request
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector




# @@ 태그로 검색
class TagSerchResource(Resource) :
    def get(self) :

        # 클라이언트로부터 데이터를 받아온다.
        keyword = request.args['keyword']
        offset = request.args['offset']
        limit = request.args['limit']

        # 디비에서 해당 키워드가 들어있는 태그에 해당되는 포스팅정보를 가져온다.
        # 디비로부터 데이터를 받아서 ,클라이언트에 보내준다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select p.*
                    from tagName tn
                    join tag t
                    on tn.id = t.tagId
                    join posting p
                    on p.id = t.postingId
                    where tn.name like '%'''+keyword+'''%'
                    group by t.postingId
                    limit '''+offset+''', '''+limit+''';'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query)

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


# @@ 포스팅의 태그내용 보는 쿼리
class TagSerchInfoResource(Resource) :
    def get(self, posting_id) :
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select tn.name as tag
                    from tagName tn
                    join tag t
                    on tn.id = t.tagId
                    join posting p
                    on p.id = t.postingId
                    where p.id = %s
                    group by tn.name;'''
            record = (posting_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 실행
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
            "items" : result_list }, 200
