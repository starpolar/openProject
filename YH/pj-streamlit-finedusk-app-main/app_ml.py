import streamlit as st
import joblib
from fbprophet import Prophet
import matplotlib.pyplot as plt
import pandas as pd
from PIL import Image

def run_ml() :
    st.subheader('미래의 미세먼지 예측')

    prophet = joblib.load('data/prophet.pkl')

    future = prophet.make_future_dataframe(periods= 1096)
    forecast = prophet.predict(future)

    st.title('')
    st.text('미래로 갈수록 미세먼지량은 많아진다고 예측되었습니다')
    img = Image.open('data/prophet_plot.png')
    st.image(img)
    # fig1 = prophet.plot(forecast) # 파일이 커서 서버에서 안돌아감
    # st.pyplot(fig1)

    year_list = ['2019', '2020', '2021', '2022']
    mouth_list = range(1, 12+1)
    day_list = range(1, 31+1)

    my_choice_year = st.selectbox('연도를 선택하세요', year_list)
    my_choice_mouth = st.selectbox('월을 선택하세요', mouth_list)
    my_choice_day = st.selectbox('일을 선택하세요', day_list)

    # year = st.number_input('연수를 입력하세요', 2019, 2022 )
    # mouth = st.number_input('월수를 입력하세요', 1, 12)
    # day = st.number_input('일수를 입력하세요', 1, 31)

    days = (str(my_choice_year) + '-' + str(my_choice_mouth) + '-' + str(my_choice_day))

    forecast = forecast.set_index('ds')
    select_days = forecast.loc[ days , 'yhat' ]
    st.subheader('미세먼지 수치의 좋고나쁨의 구간 입니다 ')
    st.write('0-30 좋음, 31-80 보통, 81-150 나쁨, 151~ 매우나쁨')
    
    st.title('')
    st.write('선택하신 날짜의 예측된 미세먼지 수치는')
    if 0 <= select_days <=30  :
        st.write(str(round(select_days)) , '이며 좋음 입니다')
    elif 31 <= select_days <=80 :
        st.write(str(round(select_days)) , '이며 보통 입니다')
    elif 81 <= select_days <=150 :
        st.write(str(round(select_days)) , '이며 나쁨 입니다')
    elif 151 <= select_days :
        st.write(str(round(select_days)) , '이며 매우나쁨 입니다')