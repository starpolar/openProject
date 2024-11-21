import streamlit as st

def run_home() :
    url = 'https://png.pngtree.com/thumb_back/fh260/background/20210902/pngtree-blue-sky-and-white-clouds-pure-sky-image_786707.jpg'
    st.image(url)
    st.subheader('경기도의 각 시별로 온실가스의 배출량과 미세먼지는')
    st.subheader('어떤 관계가 있는지에 대한 데이터들과')
    st.subheader(' ')
    st.subheader('미래의 미세먼지를 예측하는 앱 입니다')