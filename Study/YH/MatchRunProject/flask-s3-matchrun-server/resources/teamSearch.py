from flask import request
from flask_restful import Resource
from mysql_connection import get_connection
import mysql.connector
import pandas as pd

# @@ 검색어로 팀 검색
class TeamSearchResource(Resource) :
    def get(self) :
        # 클라이언트로부터 데이터를 받아온다.
        name = request.args['name']
        address = request.args['address']
        sports = request.args['sports']
        offset = request.args['offset']
        limit = request.args['limit']

        # 디비에서 해당 키워드가 들어있는 태그에 해당되는 포스팅정보를 가져온다.
       
        # 디비로부터 데이터를 받아서 ,클라이언트에 보내준다.
        try :
            # DB 연결
            connection = get_connection()

            # 쿼리문 만들기
            query = '''select *
                    from team
                    where name like '%'''+name+'''%' 
                    or address like '%'''+address+'''%'
                    or sports like '%'''+sports+'''%'
                    limit '''+offset+''', '''+limit+''';'''

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 쿼리문을 커서를 이용해서 실행한다.
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

# @@ 내팀과 실력이 비슷한 팀 실시간으로 찾기
class TeamRecomRealTimeResource(Resource) :
    def get(self, team_id) :
        
        try :
            # 데이터 업데이트
            connection = get_connection()

            #-------------------------------------------------------
            # 1. 추천을 위한 상관계수를 위해, 데이터베이스에서 데이터를 먼저 가져온다.
            
            query = '''select mr.matchReviewerTeamId as reviewer,
                        t.id as teamId, mr.skillRating, t.name
                    from matchReview mr
                    join team t
                    on mr.matchRevieweeTeamId = t.Id;'''
            
            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 실행
            cursor.execute(query)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # DB로 부터 가져온 데이터를 데이터프레임으로 만든다
            df = pd.DataFrame(data= result_list)
            
            # 피봇  테이블한후, 상관계수를 뽑는다
            matrix = df.pivot_table(values= 'skillRating',index= 'reviewer', columns= 'name')
            
            # 팀별로 50개 이상의 리뷰있는 팀만 상관계수 계산
            df = matrix.corr(min_periods= 50)
            #-------------------------------------------------------
            # 2. 이 팀의 rating 정보를, 디비에서 가져온다.

            query = '''select t.id as teamId, t.name, mr.skillRating
                    from matchReview mr
                    join team t
                    on mr.matchRevieweeTeamId = t.Id
                    where mr.matchRevieweeTeamId = %s;'''
            
            record = (team_id, )

            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 실행
            cursor.execute(query, record)

            # select 문은, 아래 함수를 이용해서, 데이터를 가져온다.
            result_list = cursor.fetchall()

            # DB로 부터 가져온, 내 팀의 rating 정보를, 데이터프레임으로 만들어준다
            df_my_rating = pd.DataFrame(data= result_list)
            #-------------------------------------------------------
            # 3. 유저 id를 데이터프레임에 넣기위한 select문

            query = '''select id, name
                    from team;'''
            
            # select 문은, dictionary = True 를 해준다.
            cursor = connection.cursor(dictionary = True)

            # 실행
            cursor.execute(query)

            result_list = cursor.fetchall()

            # DB로 부터 가져온, 팀들의 정보를, 데이터프레임으로 만들어준다
            df_team = pd.DataFrame(data= result_list)
            
            cursor.close()
            connection.close()

        except mysql.connector.Error as e :
            print(e)
            cursor.close()
            connection.close()

            return {"error" : str(e), 'error_no' : 20}, 503

        # 뽑아낸 상관관계 추천데이터에서
        # 나의 팀의 값만 내온후
        # 비중치도 계산
        similar_team = df[df_my_rating['name'][0]].dropna().sort_values(ascending= False).to_frame()
        similar_team.columns = ['Correlation']
        similar_team['Weight'] = 5 * similar_team['Correlation']

        # 팀 이름하고 같이 내역 보이게하기
        similar_team_list = similar_team.reset_index().iloc[ 1 : 19+1 , ]
        # 팀 id 같이 넣기
        last_list = pd.merge(similar_team_list, df_team, on = 'name')

        return { "result" : "success" 
            , 'similar_team_list' : last_list.to_dict('records')
                                                     # records 는 문법, 쓰면 json 형식으로 만들어주겠다
             }, 200

        
