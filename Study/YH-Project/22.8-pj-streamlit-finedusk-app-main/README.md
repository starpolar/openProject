#  Prophet을 이용한 미래의 미세먼지 예측 웹 대시보드

### 이 앱은 탭의 '데이터'를 선택하면
### 해당 시의 미세먼지 정보가 나오고, HeatMap을 통해 상관계수를 보여줍니다
### '미래의 미세먼지 예측'을 선택하면
### Prophet 을 이용한 미래의 미세먼지 예측데이터가 나오며
### 년,월,일 별로 예측된 미세먼지의량을 확인할 수 있습니다
***
## Languages
> Python

## Library
>```
> import streamlit as st
> import pandas as pd
> import joblib
> from fbprophet import Prophet
> import matplotlib.pyplot as plt
> import seaborn as sb
> import pandas as pd
> from PIL import Image
>```

## Tool
>```
> Anaconda
> Google Colab
> Visual Studio Code 
> AWS EC2
>```
***
## 주요 화면

1. 차트로 표현

> ![app-·-Streamlit](https://user-images.githubusercontent.com/105044555/190954883-410de579-7c0c-4679-86fc-6c0340e58f1f.gif)

> seaborn, matplotlib.pyplot 를 사용해 정보를 차트로 표현했습니다

2. Prophet을 이용한 예측 데이터

> ![app-·-Streamlit-_1_](https://user-images.githubusercontent.com/105044555/190955886-ade4a5a5-effc-45c0-b2ef-46687f3c3d17.gif)

> 년,월,일 별로 예측된 미세먼지의량을 확인할 수 있습니다

## URL
>http://ec2-3-39-9-192.ap-northeast-2.compute.amazonaws.com:8504/

>**EC2가 프리티어 버전이라서 로컬테스트는 문제없이 돌아가지만**
>**EC2 서버에서는 응답받지 못하는 경우가 많습니다**

***
## 데이터출처
> 1. https://data.gg.go.kr/portal/data/service/selectServicePage.do?page=1&rows=10&sortColumn=&sortDirection=&infId=GE0DUHTX3VX0GL4R0LUS26448884&infSeq=1&order=&searchWord=%EB%AF%B8%EC%84%B8%EB%A8%BC%EC%A7%80

> 2. [캐글](https://www.kaggle.com/)
