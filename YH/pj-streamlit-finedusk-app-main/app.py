import streamlit as st
from app_eda import run_eda

from app_home import run_home
from app_ml import run_ml


def main() :
    st.title('미래의 미세먼지 예측')

    menu = ['Home', '데이터', '미래의 미세먼지 예측']
    choice = st.sidebar.selectbox('메뉴를 선택하세요', menu)

    if choice == menu[0] :
        run_home()

    elif choice == menu[1] :
        run_eda()

    elif choice == menu[2] :
        run_ml()


if __name__=='__main__' :
    main()