from flask import request
from flask_jwt_extended import jwt_required, get_jwt_identity
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector


# @@ 팀 가입 신청
class TeamFollowApplyResource(Resource) :
    @jwt_required()
    def post(self, team_id) :
        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 데이터베이스에 팀정보 인서트한다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into teamFollowApply
                    (userId, teamId)
                    values
                    (%s, %s);'''
            
            record = (user_id,  team_id)

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



    # @@ 가입 신청 현황
    @jwt_required()
    def get(self,team_id) :
        # 쿼리 스트링으로 오는 데이터는 아래처럼 처리해준다.
        # request.args는 딕셔너리다

        # request.arg 코드작성 방식1
        offset = request.args.get('offset')
        limit = request.args.get('limit')

        # request.arg 코드작성 방식2
        # offset = request.args['offset']
        # limit = request.args['limit']

        # offset, limit 예외처리
        if offset is None or limit is None :
            return {'error' : '쿼리스트링 셋팅이 필요합니다.', 'error_no' : 123}, 400

        # 유저 토큰으로부터 user_id 반환
        user_id = get_jwt_identity()

        # 디비로부터 데이터를 받아서, 클라이언트에 보내준다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select u.imgUrl as profile, u.nickName as userNickName
                    from teamFollowApply tfa
                    join user u
                    on tfa.userId = u.id
                    where tfa.teamid = %s
                    limit '''+offset+''' , '''+limit+''';'''
            
            record = (team_id,)

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
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

            return {"error" : str(e), 'error_no' : 20}, 503

        return { "result" : "success" , 
                "count" : len(result_list) ,
                "items" : result_list }, 200


# 가입신청 거절
class TeamFollowApplyDeleteResource(Resource) :
    @jwt_required()
    def delete(self,team_follow_Apply_id) :
        
        # DB에서 삭제
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from teamFollowApply
                    where id =  %s;'''

            record = (team_follow_Apply_id, )

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query, record)

            # 커넥션을 커밋해줘야 한다. => 디비에 영구적으로 반영하라는 뜻
            connection.commit()

            # 자원 해제
            cursor.close()
            connection.close()

        # 정상적이지 않을때
        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {'error' : str(e)}, 503
        
        return {'result' : 'success'}, 200


# 가입 신청 승인 api
class TeamFollowApplyApprovalResource(Resource) :
    @jwt_required()
    def post(self, team_follow_Apply_id) :
        
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select * 
                    from teamFollowApply
                    where id = %s'''

            record = (team_follow_Apply_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            userId = result_list[0]['userId']
            teamId = result_list[0]['teamId']

            # 쿼리문 만들기
            query = '''delete from teamFollowApply
                    where id = %s;'''

            record = (team_follow_Apply_id, )

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query,record )

            # 쿼리문 만들기
            query = '''insert into teamFollow
                    (userId, teamId)
                    values
                    (%s, %s)'''

            record = (userId, teamId )

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
