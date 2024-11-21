package com.ygh547.matchrun;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MyTeamActivity extends AppCompatActivity {

    TextView txtChat;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_team);

        txtChat = findViewById(R.id.txtChat);

        txtChat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MyTeamActivity.this, ChatActivity.class);
            }
        });


    }
}