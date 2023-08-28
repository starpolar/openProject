from flask import Flask
from flask_jwt_extended import JWTManager
from flask_restful import Api
from config import Config
from resources.letter import LetterApplyResource
from resources.login import UserEmailUniqueResource, UserIdSearchResource, UserLoginResource, UserLogoutResource, UserNicknameUniqueResource, UserPasswordResetResource, UserPasswordSearchResource, UserRegisterResource, jwt_blacklist
from resources.match import MatchApplyApprovalResource, MatchApplyDeleteResource, MatchApplyListResource, MatchApplyResource, MatchReviewApplyResource, MyMakeTeamListResource
from resources.matchPosting import MatchPostingInfoResource, MatchPostingListResource, MatchPostingMyListResource, MatchPostingResource, MatchRepleResource
from resources.notice import NoticeApplyResource, NoticeListResource
from resources.posting import PostingInfoResource, PostingLikesResource, PostingMyResource, PostingRepleInfoResource, PostingRepleResource, PostingTeamResource
from resources.sportsCenterSearch import SportsCenterResource
from resources.tag import TagSerchInfoResource, TagSerchResource
from resources.team import TeamFollowDeleteResource, TeamFollowInfoResource, TeamInfoResource, TeamListResource, TeamReviewAvgResource
from resources.teamFollow import TeamFollowApplyApprovalResource, TeamFollowApplyDeleteResource, TeamFollowApplyResource
from resources.teamSearch import TeamRecomRealTimeResource, TeamSearchResource
from resources.user import UserInfo2Resource, UserInfoProfileResource, UserInfoReciveResource, UserInfoResource

app = Flask(__name__)


# 환경변수 셋팅
app.config.from_object(Config)

# JWT Token Library 만들기
jwt = JWTManager(app)


# 로그아웃 된 토큰이 들어있는 set을 jwt에 알려준다.
@jwt.token_in_blocklist_loader
def check_if_otken_is_revoked(jwt_header, jwt_payload) :
    jti = jwt_payload['jti']
    return jti in jwt_blacklist

api = Api(app)

# @@ <- 로 검색 #
#---------------------------------------------------------------------------------------

# 로그인 관련 API

# @@ 회원가입
api.add_resource(UserRegisterResource, '/users/register')
# @@ 로그인
api.add_resource(UserLoginResource, '/users/login')
# @@ 로그아웃
api.add_resource(UserLogoutResource, '/users/logout')
# @@ 아이디 찾기
api.add_resource(UserIdSearchResource, '/users/id/search')
# @@ 비밀번호 찾기
api.add_resource(UserPasswordSearchResource, '/users/password/search')
# @@ 비밀번호 재설정
api.add_resource(UserPasswordResetResource, '/users/password/reset/<int:user_id>')
# @@ 이메일 중복확인
api.add_resource(UserEmailUniqueResource, '/users/email')
# @@ 닉네임 중복확인
api.add_resource(UserNicknameUniqueResource, '/users/nickname')

#---------------------------------------------------------------------------------------

# 유저 관련 API

# @@ 유저 정보 가져오기
api.add_resource(UserInfoResource, '/users/<int:user_id>')
# @@ 유저 정보 토큰으로 가져오기 api
api.add_resource(UserInfo2Resource, '/users')
# @@ 유저 정보 수정하기
api.add_resource(UserInfoReciveResource, '/users')
# @@ 프로필 사진 올리기
api.add_resource(UserInfoProfileResource, '/users/profile')

#---------------------------------------------------------------------------------------

# 팀 관련 API

# @@ 팀 생성 / 내가 속한 팀 정보 가져오기
api.add_resource(TeamListResource, '/team')
# @@ 팀 상세정보 가져오기 / 팀 정보 수정 / 팀 삭제 (관리자만 삭제가능)
api.add_resource(TeamInfoResource, '/team/<int:team_id>')
# @@ 팀의 인원의 정보 가져오기 (+인원수)
api.add_resource(TeamFollowInfoResource, '/teamfollow/<int:team_id>')
# @@ 팀 탈퇴
api.add_resource(TeamFollowDeleteResource, '/teamfollow/<int:teamfollow_id>')
# @@ 팀의 매칭 리뷰의 평균값 가져오기
api.add_resource(TeamReviewAvgResource, '/match/review/avg/<int:team_id>')

#---------------------------------------------------------------------------------------

# 팀 가입 관련 API

# 가입 신청 / 가입 신청 현황
api.add_resource(TeamFollowApplyResource, '/teamfollow/apply/<int:team_id>')
# 가입 거절
api.add_resource(TeamFollowApplyDeleteResource, '/teamfollow/apply/<int:team_follow_Apply_id>')
# 가입 수락
api.add_resource(TeamFollowApplyApprovalResource, '/teamfollow/<int:team_follow_Apply_id>' )

#---------------------------------------------------------------------------------------

# 공지사항 관련 API

# @@ 공지사항 작성 / 공지사항 가져오기
api.add_resource(NoticeListResource, '/notice/<int:team_id>')
# @@ 공지사항 수정 / 공지사항 삭제
api.add_resource(NoticeApplyResource, '/notice/<int:notice_id>')

#---------------------------------------------------------------------------------------

# 포스팅 관련 API

# @@ 포스팅 작성 (+번역된 결과 태그로 저장) / 해당 팀 포스팅 가져오기
api.add_resource(PostingTeamResource, '/posting/<int:team_id>')
# @@ 내가 쓴 포스팅 가져오기
api.add_resource(PostingMyResource, '/posting/my')
# @@ 내가 쓴 포스팅 수정하기 / 내가 쓴 포스팅 삭제하기
api.add_resource(PostingInfoResource, '/posting/<int:posting_id>')
# @@ 포스팅에 좋아요 / 좋아요 취소
api.add_resource(PostingLikesResource, '/likes/<int:posting_id>')
# @@ 포스팅에 댓글 작성 / 댓글 가져오기
api.add_resource(PostingRepleResource, '/posting/reple/<int:posting_id>')
# @@ 포스팅에 댓글 삭제
api.add_resource(PostingRepleInfoResource, '/posting/reple/<int:reple_id>')

#---------------------------------------------------------------------------------------

# 태그 관련 API

# @@ 태그로 검색
api.add_resource(TagSerchResource, '/posting/tag/search')
# @@ 포스팅의 태그내용 보는 쿼리
api.add_resource(TagSerchInfoResource, '/posting/tag/search/<int:posting_id>')

#---------------------------------------------------------------------------------------

# 매칭 관련 API

# @@ 매칭 포스팅 작성
api.add_resource(MatchPostingResource, '/match/posting/<int:team_id>')
# @@ 모든 매칭 포스팅 가져오기
api.add_resource(MatchPostingListResource, '/match/posting')
# @@ 내가 쓴 매칭 포스팅 가져오기
api.add_resource(MatchPostingMyListResource, '/match/posting/my')
# @@ 내가 쓴 매칭 포스팅 수정 / 삭제
api.add_resource(MatchPostingInfoResource, '/match/posting/<int:matchposting_id>')
# @@ 매칭 포스팅에 댓글 작성 / 댓글 가져오기
api.add_resource(MatchRepleResource, '/match/reple/<int:matchposting_id>')

#---------------------------------------------------------------------------------------

# 매칭 신청 관련 API

# 매칭 신청
api.add_resource(MatchApplyResource, '/match/apply/<int:match_follower_team_id>/<int:match_followee_team_id>')
# @@ 내가 만든 팀 가져오기
api.add_resource(MyMakeTeamListResource, '/team/make')
# 매칭 신청 현황
api.add_resource(MatchApplyListResource, '/match/apply/<int:team_id>')
# 매칭 거절
api.add_resource(MatchApplyDeleteResource, '/match/apply/<int:match_apply_id>')
# 매칭 수락
api.add_resource(MatchApplyApprovalResource, '/match/<int:match_apply_id>')
# @@ 매칭 리뷰 작성
api.add_resource(MatchReviewApplyResource, '/match/review/<int:matching_id>')


#---------------------------------------------------------------------------------------

# 팀 검색 관련 API

# @@ 검색어로 팀 검색
api.add_resource(TeamSearchResource, '/team/search')
# @@ 내팀과 실력이 비슷한 팀 실시간으로 찾기
api.add_resource(TeamRecomRealTimeResource, '/team/realtime/<int:team_id>')

#---------------------------------------------------------------------------------------

# 체육관 검색 관련 API

# @@ 체육관 검색
api.add_resource(SportsCenterResource, '/sportscenter/search')

#---------------------------------------------------------------------------------------

# 쪽지 관련 API

# @@ 쪽지 보내기 / 내가 받은 쪽지 가져오기
api.add_resource(LetterApplyResource, '/letter')

if __name__ == '__main__' :
    app.run()