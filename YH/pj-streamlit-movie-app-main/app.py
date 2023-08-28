import streamlit as st
import pandas as pd

from tkinter.tix import COLUMN
from pyparsing import empty

import pickle

from googletrans import Translator

# 레이아웃 과정
st.set_page_config(layout="wide")
empty1,con0,empty2 = st.columns([1,1.0,0.9])
empty1,con0_1,empty2 = st.columns([0.6,0.5,0.3])
empty1,con1,empty2 = st.columns([0.9,1.0,0.9])
empty1,con2,con3,empty2 = st.columns([0.9,0.5,0.5,0.9])
empty1,con4,empty2 = st.columns([0.9,0.1,0.6])
empty1,con5,empty2 = st.columns([0.9,0.2,0.5])
empty1,con6,empty2 = st.columns([0.8,1,0.3])

def main() :
    
    with con0 :
        st.image('https://thumbs.gfycat.com/GaseousBlueColt.webp')
                       
    with con0_1 :
        st.title('영화 추천')
        st.title('')

    with con1 :
        df_corr = pd.read_csv('data/df_corr.csv', index_col=0)
        col = df_corr.columns

        choice_movie = st.selectbox('영화 선택', col)

    with con2 :
        # 크롤링한 이미지URL 데이터를 dict에 저장 했고, 불러오는 과정
        with open('data/url_dict.pickle', 'rb') as f:
            url_dict = pickle.load(f)

        url_dict = url_dict[choice_movie]
        st.image(url_dict)

    with con3 :
        # 데이터의 줄거리 부분을 가져왔고
        # 구글 번역 API를 통해 변역함
        st.text('줄거리')

        df_overview = pd.read_csv('data/df_overview.csv', index_col=0)
        over = df_overview.set_index('title').loc[choice_movie][0]
               
        translator = Translator()
        result = translator.translate(over, dest="ko")
        st.markdown(result.text)

        if st.checkbox('원본보기') :
            st.markdown(over)

    
    
    with con4 :
        st.title('')
        choice_rating = st.selectbox('별점 선택', range(1, 5+1))
   
    with con5 :

        # 유저의 별점 저장하는 과정
        user_rating_reset = pd.read_csv('data/user_rating_reset.csv', index_col= 0)
        user_rating = pd.read_csv('data/user_rating.csv', index_col= 0)
        user_rating['rating'] = user_rating['rating'].astype(int)
        
        if st.button('저장하기') :
            
            if ( user_rating.loc[ user_rating['userId'] == 999 , ]['userId'].tolist() ) == [] :
                user_rating = user_rating_reset.append( { 'title' : choice_movie , 'userId' : 999, 'rating' : int(choice_rating) }, ignore_index=True )
                user_rating.to_csv('data/user_rating.csv')
                
            elif ( ( (user_rating.loc[ user_rating['userId'] == 999 , ])['userId'] == 999).tolist() )[0] :
                user_rating = user_rating.append( { 'title' : choice_movie , 'userId' : 999, 'rating' : int(choice_rating) }, ignore_index=True )
                user_rating.to_csv('data/user_rating.csv')

        # 저장된 데이터를 삭제하는 과정        
        if st.checkbox('삭제하기') :

            if st.button('리셋하기') :
                user_rating = user_rating_reset
                user_rating.to_csv('data/user_rating.csv')

            if st.checkbox('부분 삭제하기') :
                if list(user_rating['userId']) == [] :
                    st.markdown('삭제할 데이터가 없습니다')
                else :
                    user_title = list(enumerate(user_rating['title'].values))
                    user_title_select = st.selectbox('삭제할 영화 선택', user_title)
                    if st.button('삭제') :
                        user_rating = user_rating.drop(index= user_title_select[0]
                        , axis=0)
                        user_rating = user_rating.reset_index(drop= True)
                        user_rating.to_csv('data/user_rating.csv')

    with con6 :
        st.title('')
        st.subheader('나의 영화들')

        st.dataframe(user_rating[['title', 'rating']])

        st.title('')
        if st.button('내가 본 영화들의 추천 영화 보기') :
            st.text('추천 영화 5개')

            # 내가 영화에 준 별점을 상관계수에 채우는 과정
            similar_movies_list = pd.DataFrame()

            for i in range( user_rating.shape[0] ) :
                movie_name = user_rating['title'][i]
                recom_movies = df_corr[movie_name].sort_values(ascending=False).to_frame()
                recom_movies.columns = ['correlation']
                recom_movies['weight'] = user_rating['rating'][i] * recom_movies['correlation']
                similar_movies_list = similar_movies_list.append( recom_movies )

            # 내 영화들 지우고 추천영화만 정렬해서 보여주는 과정
            similar_movies_list = similar_movies_list.sort_values('weight' , ascending=False)
            user_rating['title'].to_list()
            similar_movies_list.drop( user_rating['title'].to_list() , axis=0,  inplace= True )

            similar_movie = similar_movies_list.groupby('title')['weight'].max().sort_values(ascending = False).to_frame().reset_index()
            similar_movie = similar_movie.loc[ : , 'title' ].to_frame().head(5)

            st.dataframe(similar_movie)


if __name__=='__main__' :
    main()