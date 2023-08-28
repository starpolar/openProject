# Match Run Server

## Language <br/>
[![Python Badge](https://img.shields.io/badge/Python-3776AB?style=flat&logo=Python&logoColor=white)](https://www.python.org/downloads/)<br/>

## Tool<br/>
[![Google Colab Badge](https://img.shields.io/badge/Google%20Colab-F9AB00?style=flat&logo=Google%20Colab&logoColor=white)](https://colab.research.google.com/?hl=ko)
[![Visual Studio Code Badge](https://img.shields.io/badge/Visual%20Studio%20Code-007ACC?style=flat&logo=Visual%20Studio%20Code&logoColor=white)](https://code.visualstudio.com/download)
[![MySQL Badge](https://img.shields.io/badge/MySQL-4479A1?style=flat&logo=MySQL&logoColor=white)](https://www.mysql.com/downloads/)
[![Postman Badge](https://img.shields.io/badge/Postman-FF6C37?style=flat&logo=Postman&logoColor=white)](https://www.postman.com/downloads/)<br/>

## Library<br/>
[![NumPy Badge](https://img.shields.io/badge/NumPy-013243?style=flat&logo=NumPy&logoColor=white)](https://numpy.org/install/)
[![pandas Badge](https://img.shields.io/badge/pandas-150458?style=flat&logo=pandas&logoColor=white)](https://pandas.pydata.org/)
[![mysql-connector-python Badge](https://img.shields.io/badge/mysql%20connector-python-3776AB?style=flat&logo=mysql%20connector-python&logoColor=white)](https://pypi.org/project/mysql-connector-python/)
[![flask-restful Badge](https://img.shields.io/badge/flask-restful-000000?style=flat&logo=flask-restful&logoColor=white)](https://flask-restful.readthedocs.io/en/latest/installation.html)
[![psycopg2-binary Badge](https://img.shields.io/badge/psycopg2-binary-FF6C37?style=flat&logo=psycopg2-binary&logoColor=white)](https://pypi.org/project/psycopg2-binary/)
[![passlib Badge](https://img.shields.io/badge/passlib-512BD4?style=flat&logo=passlib&logoColor=white)](https://pypi.org/project/passlib/)
[![email-validator Badge](https://img.shields.io/badge/email-validator-FF6C37?style=flat&logo=email-validator&logoColor=white)](https://pypi.org/project/email-validator/)
[![Flask-JWT-Extended Badge](https://img.shields.io/badge/Flask-JWT%20Extended-FF6C37?style=flat&logo=Flask-JWT%20Extended&logoColor=white)](https://pypi.org/project/Flask-JWT-Extended/)
<br/>

## AWS<br/>
[![Amazon RDS Badge](https://img.shields.io/badge/AWS%20RDS-4479A1?style=flat&logo=Amazon%20RDS&logoColor=white)](https://aws.amazon.com/ko/rds/)
[![Amazon IAM Badge](https://img.shields.io/badge/AWS%20IAM-red?style=flat&logo=Amazon%20IAM&logoColor=white)](https://aws.amazon.com/ko/rds/)
[![Amazon S3 Badge](https://img.shields.io/badge/AWS%20S3-569A31?style=flat&logo=Amazon%20S3&logoColor=white)](https://aws.amazon.com/ko/s3/)
[![Amazon Lambda Badge](https://img.shields.io/badge/AWS%20Lambda-FF9900?style=flat&logo=AWS%20Lambda&logoColor=white)](https://aws.amazon.com/ko/lambda/)
[![Amazon API Gateway Badge](https://img.shields.io/badge/AWS%20API%20Gateway-blue?style=flat&logo=AWS%20API%20Gateway&logoColor=white)](https://aws.amazon.com/ko/api-gateway/)
[![Amazon CloudWatch Badge](https://img.shields.io/badge/AWS%20CloudWatch-FF4F8B?style=flat&logo=AWS%20CloudWatch&logoColor=white)](https://aws.amazon.com/ko/cloudwatch/)
[![Amazon Rekognition Badge](https://img.shields.io/badge/AWS%20Rekognition-blueviolet?style=flat&logo=AWS%20Rekognition&logoColor=white)](https://aws.amazon.com/ko/rekognition/)
<br/>
<br/>

## Server Architecture

<img src = "https://user-images.githubusercontent.com/105832364/188270446-5bc3024a-beeb-4ffa-b53f-a39ab2c2ba28.png" width="85%" height="150%"> <br/>
<br/>
<br/>

## 주요 기능

<img src = "https://user-images.githubusercontent.com/105832364/188272094-5c8707b9-8ab4-40a2-a2ba-d9bcaf839c76.png" width="85%" height="100%"> <br/>
- AWS Rekognition을 이용해 탐지된 객체의 레이블을 태그로 저장 할 수 있습니다. <br/>
- 태그로 저장되는 레이블은 Naver Papago Open API를 이용해 한글로 번역되어 저장 됩니다. <br/>
- 검색어를 입력하면 저장된 태그를 이용해 연관된 포스팅을 불러와 이미지와 내용을 확인 할 수 있습니다. <br/>
<br/>
<br/>

<img src = "https://user-images.githubusercontent.com/105832364/188272544-22a7d9a6-d32f-4890-aeda-0ca14be9a5ef.png" width="85%" height="100%"> <br/>
- 공공데이터 Open API를 이용해 xml로 파싱한 데이터를 Google Colab으로 데이터 가공 후 RDS에 저장하였으며,<br/>
가공한 데이터를 기반으로 Google Maps API를 이용해 전국 8만여개의 체육시설 지도데이터를 검색 할 수 있습니다.
<br/>
<br/>

<img src = "https://user-images.githubusercontent.com/105832364/188272961-d299c44b-a708-444a-905f-0441ccb2feda.png" width="85%" height="100%"> <br/>
<img src = "https://user-images.githubusercontent.com/105832364/188273048-f24cc578-bd02-4def-9357-9a8518d18d40.png" width="85%" height="100%"> <br/>
- 상대팀과 매칭을 진행하기 위해 매칭 포스팅을 이용해 매칭상대를 모집 할 수 있습니다.
- 팀 상세정보에서 매칭 신청을 할 수 있으며, 각 팀의 팀 설정의 매칭 신청 현황에서 수락과 거절로 관리 할 수 있습니다.
<br/>
<br/>

## 테이블 명세서<br/>
### [ERD CLOUD 보러가기]
[ERD CLOUD 보러가기]: https://www.erdcloud.com/d/EcqFpAeexdMZx5ec3
<img src = "https://user-images.githubusercontent.com/105832364/188270869-c6786083-f0f6-4563-9aa2-36980c4bba10.png" width="85%" height="100%"> <br/>
<br/>
<br/>


## API Reference<br/>
### [API Reference 보러가기]
[API Reference 보러가기]: https://graphene911.gitbook.io/matchrun-api-docs/
<img src = "https://user-images.githubusercontent.com/105832364/188273423-c68b9685-5b7b-433f-8d61-4457a7af542f.png" width="85%" height="100%"> <br/>

