# 추천 시스템을 활용한 영화 검색 웹 대시보드

### 이 앱은 영화를 선택하면 정보가 나오고,
### 선택한 영화에 유저가 별점을 매겨서 저장할수 있으며
### 유저의 별점을 실시간으로 반영해 영화 추천을 해줍니다
***
## Languages
> Python

## Library
>```
> import streamlit as st
> import pandas as pd
> from tkinter.tix import COLUMN
> from pyparsing import empty
> import pickle
> from googletrans import Translator
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
### 영화 정보
![1](https://user-images.githubusercontent.com/105044555/190952921-256684d4-444a-4f51-8f8c-b2b1b194ec74.png)

### 추천 영화
![2](https://user-images.githubusercontent.com/105044555/190953147-46990637-f958-404c-ade8-9c68ed596b21.png)

***
## 주요 기술

1. 레이아웃
>```
>from tkinter.tix import COLUMN
>from pyparsing import empty
>```
>두개의 라이브러리를 사용해서 레이아웃 했습니다

2. 영화 정보들

* 이미지 크롤링
>1. **selenium** 을 이용한 크롤링을 하고,
>2. 이미지 URL만 따로 dict 형식에 저장을 한후
>3. 
>```
>import pickle
>```
>pickle 라이브러리를 이용해서 파일로 저장한후
>메인 소스파일에 불러왔습니다

* 줄거리 / 구글번역API 사용
>* 설치 과정
>```
>pip install googletrans==4.0.0-rc1
>```
>위에 코드로 아나콘다 프롬프트에 설치를 합니다
>
>* 버전을 선택하는 이유는,
>pip install googletrans 만 입력해 설치하게되면 3.0 버전으로 설치되게 되고
>오류가 많아서 사용이 어렵습니다
>그러므로 4.0 버전으로 설치를 해야합니다

3. 저장하기 
>* csv 파일을 독자적으로 만들어 놓고
>유저가 입력할 때마다 입력된 내용을
>csv 파일에 저장하는 방식으로 했습니다
>
>* 문제점은 리셋버튼을 누르지 않는다면은
>서버에 영구적으로 남는다는 것입니다

4. 삭제하기
>* 전체 리셋하기와
>* 부분만 삭제할 수 있게 했습니다

5. 영화추천
>* 유저의 별점을 파일에 저장하고
>작업해놓은 상관계수 데이터프레임에 대입해서
>관련 순위가 높은 5개로 추려 추천하게 했습니다
***

## URL
http://ec2-3-39-9-192.ap-northeast-2.compute.amazonaws.com:8503/

***
## 데이터출처
https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset?select=movies_metadata.csv
