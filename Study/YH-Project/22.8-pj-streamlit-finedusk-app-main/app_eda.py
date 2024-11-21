import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sb

# %matplotlib inline

def run_eda() :
    # # import platform

    # # from matplotlib import font_manager, rc
    # import matplotlib.font_manager as fm
    # import matplotlib
    # # plt.rcParams['axes.unicode_minus'] = False

    # # if platform.system() == 'Darwin':
    # #     rc('font', family='AppleGothic')
    # # elif platform.system() == 'Windows':
    #     # path = "c:/Windows/Fonts/malgun.ttf"
    # fm.get_fontconfig_fonts()
    # # path = "/usr/share/fonts/nanum/NanumGothicBold.ttf"
    # path = "/usr/share/fonts/nanum/NanumGothic.ttf"
    # font_name = fm.FontProperties(fname=path).get_name()
    # matplotlib.rc('font', family=font_name)
    # # else:
    # #     print('Unknown system... sorry~~~~')

    # import matplotlib.pyplot as plt
    # import matplotlib.font_manager as fm
    # import matplotlib

    # fm.get_fontconfig_fonts()
    # path = '/usr/share/fonts/nanum/NanumMyeongjo.ttf'
    # font_name = fm.FontProperties(fname=path).get_name()
    # matplotlib.rc('font', family=font_name)

    # import matplotlib as mpl

    # # 유니코드 깨짐현상 해결
    # mpl.rcParams['axes.unicode_minus'] = False

    # # 나눔고딕 폰트 적용
    # plt.rcParams["font.family"] = 'NanumGothic'

    import platform

    from matplotlib import font_manager, rc
    plt.rcParams['axes.unicode_minus'] = False

    if platform.system() == 'Linux':
        rc('font', family='NanumGothic')
        

    st.subheader('2019년도 온실가스 배출량과 미세먼지량의 평균데이터')
    st.title('')

    df = pd.read_csv('data/df.csv')
    df2 = pd.read_csv('data/df2.csv')

    radio_menu = ['데이터프레임', '통계치']
    selected = st.radio('선택하세요', radio_menu)

    if selected == radio_menu[0] :
        st.text('컬럼을 선택하면 정렬할 수 있습니다')
        st.dataframe( df )
    elif selected == radio_menu[1] :
        st.text('컬럼을 선택하면 정렬할 수 있습니다')
        st.dataframe( df.describe() )

    st.title('')
    selected_col = st.selectbox('원하는 시의 데이터를 선택할 수 있습니다', list(df['시군명']))

    df_data = df.loc[df['시군명'] == selected_col, ]

    st.dataframe(df_data)

    st.title('')
    st.text('상관관계들을 나타낸 heatmap 입니다')
    fig1 = plt.figure()
    sb.heatmap(data= df.corr(), annot=True, fmt='.2f', 
        vmin = -1, vmax = 1, cmap='coolwarm', linewidths=0.5)
    st.pyplot(fig1)

    st.title('')
    st.text('선택한 컬럼들끼리의 상관계수를 보여줍니다')
    selected_list = st.multiselect('컬럼들 선택', df.columns[1:])
    
    if len(selected_list) >= 2 :
        fig2 = sb.pairplot(data= df[selected_list])
        st.pyplot(fig2)

        st.text('선택하신 컬럼끼리의 상관계수 입니다.')
        st.dataframe( df[selected_list].corr() )