package com.ygh547.matchrun.api;

import com.ygh547.matchrun.model.User2;
import com.ygh547.matchrun.model.UserRes;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.Header;
import retrofit2.http.POST;

public interface TeamApi {

    // 회원가입 API
    @POST("/team")
    Call<UserRes> register(@Body User2 user);

    // 로그인 API
    @POST("/users/login")
    Call<UserRes> login(@Body User2 user);

    // 로그아웃 API
    @POST("/users/logout")
    Call<UserRes> logout(@Header("Authorization") String token);
}
