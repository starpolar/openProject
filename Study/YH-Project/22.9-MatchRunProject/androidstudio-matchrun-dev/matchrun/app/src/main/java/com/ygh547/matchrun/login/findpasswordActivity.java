package com.ygh547.matchrun.login;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;

import com.ygh547.matchrun.R;
import com.ygh547.matchrun.api.NetworkClient;
import com.ygh547.matchrun.api.UserApi;
import com.ygh547.matchrun.config.Config;
import com.ygh547.matchrun.model.User2;
import com.ygh547.matchrun.model.UserRes;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;

public class findpasswordActivity extends AppCompatActivity {

    private Spinner question2;
    ArrayList<String> arrayList;
    ArrayAdapter<String> arrayAdapter2;
    private ProgressDialog dialog;

    EditText editemail2;
    EditText editquestionAn2;
    ImageView imgpasswordser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_findpassword);

        editemail2 = findViewById(R.id.editemail2);
        editquestionAn2 = findViewById(R.id.editquestionAn2);
        imgpasswordser = findViewById(R.id.imgpasswordser);

        arrayList = new ArrayList<>();
        arrayList.add("본인확인질문");
        arrayList.add("나의 보물 1호는?");
        arrayList.add("애완동물의 이름은?");
        arrayList.add("아버지 성함은?");
        arrayList.add("어머니 성함은?");
        arrayList.add("가장 기억의 남는 추억의 장소는?");
        arrayList.add("어린 시절 별명은 무엇입니까?");

        arrayAdapter2 = new ArrayAdapter<>(getApplicationContext(),
                android.R.layout.simple_spinner_dropdown_item,
                arrayList);

        question2 = (Spinner)findViewById(R.id.question2);
        question2.setAdapter(arrayAdapter2);
        question2.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
//                Toast.makeText(getApplicationContext(),arrayList.get(i)+"가 선택되었습니다.",
//                        Toast.LENGTH_SHORT).show();
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });

        imgpasswordser.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String email = editemail2.getText().toString().trim();
                if(email.isEmpty()){
                    Toast.makeText(findpasswordActivity.this, "이름을 입력하세요.", Toast.LENGTH_SHORT).show();
                    return;
                }

                String questionAn2 = editquestionAn2.getText().toString().trim();
                if(questionAn2.isEmpty()){
                    Toast.makeText(findpasswordActivity.this, "정답을 입력하세요.", Toast.LENGTH_SHORT).show();
                    return;
                }

                Retrofit retrofit = NetworkClient.getRetrofitClient(findpasswordActivity.this);
                UserApi api = retrofit.create(UserApi.class);

                User2 user2 = new User2(email,question2, questionAn2);
                Call<UserRes> call = api.passwordsearch(user2);

//                call.enqueue(new Callback<UserRes>() {
//                    @Override
//                    public void onResponse(Call<UserRes> call, Response<UserRes> response) {
//
//                        if(response.isSuccessful()){
//
//                            UserRes userRes = response.body();
//                            String password = userRes.getPassword();
//
//                            SharedPreferences sp = getApplication().getSharedPreferences(Config.PREFERENCES_NAME, MODE_PRIVATE);
//                            SharedPreferences.Editor editor = sp.edit();
//                            editor.putString("password", password);
//                            editor.apply();
//
//                            Intent intent = new Intent(findpasswordActivity.this, SecondfindpasswordActivity.class);
//                            startActivity(intent);
//                            finish();
//
//                        }else{
//
//                        }
//                    }
//
//                    @Override
//                    public void onFailure(Call<UserRes> call, Throwable t) {
//
//                    }
//                });

//
            }
        });
    }
}