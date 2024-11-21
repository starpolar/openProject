# 시계열 예측 모델 개발 프로젝트

&nbsp;
## Data Source
> https://www.kaggle.com/datasets/khairullahhamsafar/hotels-booking-data-cleaned-version
## Model
> GRU

&nbsp;
## Progress
### Data Parsing
> 데이터 분석후에 어떤 데이터로 시계열 학습을 할지 목적 수립.
>> 연도, 월, 날짜가 다른 컬럼으로 이루어져있고 평균 요금 지표가 있으니 날짜별로 요금을 조인시켜 날짜별 평균 요금 합산하여 전처리.
