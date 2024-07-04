from flask import request
from flask_jwt_extended import jwt_required, get_jwt_identity
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector



# @@ 매칭 신청
class MatchApplyResource(Resource) :
    def post(self, match_follower_team_id, match_followee_team_id) :

        data = request.get_json()
        
        # DB에 팀정보 인서트한다.
        try :

            # 둘중 작은값을 무조건 앞으로가게 처리하고
            # 두 컬럼의 값을 유니크 처리함으로서
            # 중복 데이터 입력을 방지함
            if match_follower_team_id > match_followee_team_id :
                rettle_team_id = match_followee_team_id
                grande_team_id = match_follower_team_id
                match_follower_team_id = rettle_team_id
                match_followee_team_id = grande_team_id

            # 데이터 insert 
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into matchApply
                    (matchFollowerTeamId, matchFolloweeTeamId, matchDay)
                    values
                    (%s, %s, %s);'''
            
            record = (match_follower_team_id, match_followee_team_id, data['matchDay'])

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

# @@ 내가 만든 팀 가져오기
class MyMakeTeamListResource(Resource) :
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
            query = '''select *
                    from team
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


# @@ 매칭 현황
class MatchApplyListResource(Resource) :
    def get(self, team_id) :
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

        # DB로부터 데이터를 받아서, 클라이언트에 보내준다.
        try :
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select t.id, t.imgUrl, t.name, m.matchDay, m.reviewResult
                    from matching m
                    join team t
                    on m.matchFollowerTeamId = t.id or m.matchFolloweeTeamId = t.id
                    where not t.id = %s
                    limit '''+offset+''' , '''+limit+''';'''

            record = (team_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해 실행한다.
            cursor.execute(query, record)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # print(result_list)

            # print(result_list)

            # 중요! 디비에서 가져온 timestamp 난
            # 파이썬의 datetime 으로 자동 변경된다.
            # json은 datetime 같은게 없다 그냥 문자열이다
            # 문제는! 이 데이터를 json 으로 바로 보낼 수 없으므로,
            # 문자열로 바꿔서 다시 저장해서 보낸다.
            i = 0
            for record in result_list :
                result_list[i]['matchDay'] = record['matchDay'].isoformat()
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
                "count" : len(result_list) ,
                "items" : result_list }, 200


# @@ 매칭신청 거절
class MatchApplyDeleteResource(Resource) :
    @jwt_required()
    def delete(self, match_apply_id) :
        
        # DB에서 삭제
        try :
            # 데이터 삭제
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''delete from matchApply
                    where id = %s;'''

            record = (match_apply_id, )

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


# @@ 매칭 신청 수락
class MatchApplyApprovalResource(Resource) :
    @jwt_required()
    def post(self, match_apply_id) :
        # 디비 업데이트 실행코드
        try :
            # 데이터 업데이트
            # DB에 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select * 
                    from matchApply
                    where id = %s'''

            record = (match_apply_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해 실행한다.
            cursor.execute(query, record )

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            match_follower_team_id = result_list[0]['matchFollowerTeamId']
            match_followee_team_id = result_list[0]['matchFolloweeTeamId']
            matchDay = result_list[0]['matchDay']

            # 쿼리문 만들기
            query = '''delete from matchApply
                    where id = %s;'''

            record = (match_apply_id, )

            # 커서를 가져온다.
            cursor = connection.cursor()

            # 쿼리문을 커서를 이용해서 실행한다.
            cursor.execute(query,record )

            # 쿼리문 만들기
            query = '''insert into matching
                    (matchFollowerTeamId, matchFolloweeTeamId, matchDay)
                    values
                    (%s, %s, %s)'''

            record = (match_follower_team_id, match_followee_team_id, matchDay )

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

# @@ 매칭 리뷰 작성
class MatchReviewApplyResource(Resource) :
    def post(self, matching_id) :

        # {
        #     "matchReviewerTeamId": 1,
        #     "matchRevieweeTeamId": 1,
        #     "mannerRating": 1,
        #     "skillRating": 1
        # }

        # 클라이언트가 body에 보내준 json을 받아온다.
        data = request.get_json()

        try :
            # DB연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''insert into matchReview
                    (matchReviewerTeamId, matchRevieweeTeamId, mannerRating, skillRating)
                    values
                    (%s, %s, %s, %s);'''

            # 클라이언트 상에서
            # wer 팀 wee 팀 두개다 가져오자
            # wer -> 내가 들어가있던 팀으로
            # wee -> 현황에 표시된 팀 id로
            record = (data['matchReviewerTeamId'], data['matchRevieweeTeamId'], data['mannerRating'], data['skillRating'] )

            # 커서를 가져온다.
            cursor = connection.cursor()

            
            cursor.execute(query, record)

             # 쿼리문 만들기
            query = '''update matching
                    set reviewResult = 1
                    where id = %s'''

            record = (matching_id, )

            # 커서를 가져온다.
            cursor = connection.cursor()

            
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
