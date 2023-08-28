package com.ygh547.matchrun.login;

import com.android.volley.AuthFailureError;
import com.android.volley.Response;
import com.android.volley.toolbox.StringRequest;

import java.util.HashMap;
import java.util.Map;

public class RegisterRequest extends StringRequest {

    //서버 url 설정(php파일 연동)
    final static  private String URL="http://127.0.0.1:5000";
    private Map<String,String>map;



    public RegisterRequest(String userID, String userPass, String userrePass, String userQnA, String userName, String usetNiname, String useraddress, String userreaddress, Response.Listener<String>listener) {
        super(Method.POST,URL,listener,null);//위 url에 post방식으로 값을 전송
        map=new HashMap<>();
        map.put("userId",userID);
        map.put("userPass",userPass);
        map.put("userrePass",userrePass);
        map.put("userQnA",userQnA);
        map.put("userName",userName);
        map.put("usetNiname",usetNiname);
        map.put("useraddress",useraddress);
        map.put("userreaddress",userreaddress);
    }

    @Override
    protected Map<String, String> getParams() throws AuthFailureError {
        return map;
    }
}
