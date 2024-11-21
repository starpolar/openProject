package com.ygh547.matchrun.api;

import com.ygh547.matchrun.model.User2;
import com.ygh547.matchrun.model.UserRes;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.Header;
import retrofit2.http.POST;
import retrofit2.http.PUT;

// 함수랑 상수만 있는것을 interface
public interface UserApi {

    // 회원가입 API
    @POST("/users/register")
    Call<UserRes> register(@Body User2 user2);

    // 로그인 API
    @POST("/users/login")
    Call<UserRes> login2(@Body User2 user2);

    // 로그아웃 API
    @POST("/users/logout")
    Call<UserRes> logout(@Header("Authorization") String token);

    // 아이디 찾기 API
    @GET("/users/id/search")
    Call<UserRes> idsearch(@Body User2 user2);

    // 비밀번호 찾기 API
    @GET("/users/password/search")
    Call<UserRes> passwordsearch(@Body User2 user2);

    @PUT("/users/password/reset/<int:userId>")
    Call<UserRes> passwordreset(@Body User2 user2);

    @GET("/users/email")
    Call<UserRes> idcheck();

    @GET("/users/nickname")
    Call<UserRes> nickcheck();


}


