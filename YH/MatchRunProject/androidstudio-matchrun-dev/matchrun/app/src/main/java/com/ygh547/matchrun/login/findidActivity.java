package com.ygh547.matchrun.login;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
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

public class findidActivity extends AppCompatActivity {

    private Spinner question;
    ArrayList<String> arrayList;
    ArrayAdapter<String> arrayAdapter;
    private ProgressDialog dialog;

    EditText editname;
    EditText editsubemail;
    EditText editquestionAn;
    ImageView imgSer1;

    Cursor cursor;

    ArrayList<User2> userList = new ArrayList<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_findid);

        editname = findViewById(R.id.editname);
        editsubemail = findViewById(R.id.editsubemail);
        editquestionAn = findViewById(R.id.editquestionAn);
        imgSer1 = findViewById(R.id.imgSer1);


        arrayList = new ArrayList<>();
        arrayList.add("본인확인질문");
        arrayList.add("앱의 이름은?");
        arrayList.add("나의 보물 1호는?");
        arrayList.add("애완동물의 이름은?");
        arrayList.add("아버지 성함은?");
        arrayList.add("어머니 성함은?");
        arrayList.add("가장 기억의 남는 추억의 장소는?");
        arrayList.add("어린 시절 별명은 무엇입니까?");

        arrayAdapter = new ArrayAdapter<>(getApplicationContext(),
                android.R.layout.simple_spinner_dropdown_item,
                arrayList);

        question = (Spinner) findViewById(R.id.question);
        question.setAdapter(arrayAdapter);
        question.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
//                Toast.makeText(getApplicationContext(),arrayList.get(i)+"가 선택되었습니다.",
//                        Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });

        Log.d("Mylog", question+"");

        imgSer1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String name = editname.getText().toString().trim();
                if (name.isEmpty()) {
                    Toast.makeText(findidActivity.this, "이름을 입력하세요.", Toast.LENGTH_SHORT).show();
                    return;
                }
                String subemail = editsubemail.getText().toString().trim();
                if (subemail.isEmpty()) {
                    Toast.makeText(findidActivity.this, "서브 이메일를 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }
                String questionAn = editquestionAn.getText().toString().trim();
                if (questionAn.isEmpty()) {
                    Toast.makeText(findidActivity.this, "본인확인 질문을 입력해 주세요.", Toast.LENGTH_SHORT).show();
                }

                Retrofit retrofit = NetworkClient.getRetrofitClient(findidActivity.this);
                UserApi api = retrofit.create(UserApi.class);

//                User2 user2 = new User2(name, subemail, question, questionAn);
//                Call<UserRes> call = api.idsearch(user2);
//
//                call.enqueue(new Callback<UserRes>() {
//                    @Override
//                    public void onResponse(Call<UserRes> call, Response<UserRes> response) {
//                        dismissProgress();
//
//                        if (response.isSuccessful()) {
//
//                            UserRes userRes = response.body();
//                            String email = userRes.getEmail();
//
//                            SharedPreferences sp = getApplication().getSharedPreferences(Config.PREFERENCES_NAME, MODE_PRIVATE);
//                            SharedPreferences.Editor editor = sp.edit();
//                            editor.putString("email", email);
//                            editor.apply();
//
//                            Intent intent = new Intent(findidActivity.this, SecondfindidActivity.class);
//                            startActivity(intent);
//                            finish();
//
//                        } else {
//
//                        }
//                    }

//                    @Override
//                    public void onFailure(Call<UserRes> call, Throwable t) {
//                        dismissProgress();
//                    }
//                });
            }
        });
    }






    void showProgress(String message){
        dialog = new ProgressDialog(this);
        dialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        dialog.setMessage(message);
        dialog.show();
    }

    void dismissProgress(){
        dialog.dismiss();
    }

}