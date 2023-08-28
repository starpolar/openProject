package com.ygh547.matchrun;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.util.Patterns;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.ygh547.matchrun.adapter.ChatAdapter;
import com.ygh547.matchrun.api.NetworkClient;
import com.ygh547.matchrun.api.UserApi;
import com.ygh547.matchrun.config.Config;
import com.ygh547.matchrun.login.LoginActivity;
import com.ygh547.matchrun.model.ChatData;
import com.ygh547.matchrun.model.User2;
import com.ygh547.matchrun.model.UserRes;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;

public class ChatActivity extends AppCompatActivity {
    private RecyclerView recyclerView;
    public RecyclerView.Adapter adapter;
    private RecyclerView.LayoutManager mLayoutManager;
    private List<ChatData> chatList;
    private String nick = "nick2";

    private String nick2;
    private EditText editChat;
    private Button btnSend;
    private DatabaseReference myRef;





    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_PAN);
        recyclerView = findViewById(R.id.recyclerView);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(ChatActivity.this));



        chatList = new ArrayList<>();
        adapter = new ChatAdapter(chatList, ChatActivity.this, nick);
        recyclerView.setAdapter(adapter);

        btnSend = findViewById(R.id.btnSend);
        editChat = findViewById(R.id.editChat);



//        Intent intent = getIntent();
//        Bundle bundle = intent.getExtras();
//        String access_token = bundle.getString("access_token");



        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String msg = editChat.getText().toString();


                if (msg != null) {
                    ChatData chat = new ChatData();
                    chat.setNickName(nick);
                    chat.setMsg(msg);
                    myRef.push().setValue(chat);
                }
                showItemList();
            }
        });

        // Write a message to the database
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        myRef = database.getReference("message");

//        ChatData chat = new ChatData();
//        chat.setNickName(nick);
//        chat.setMsg("hi");
//        myRef.setValue(chat);

        myRef.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
                Log.d("CHATCAHT", snapshot.getValue().toString());

                ChatData chat = snapshot.getValue(ChatData.class);
                ((ChatAdapter) adapter).addChat(chat);
            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot snapshot) {
            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });
    }



    public void showItemList(){
        recyclerView.scrollToPosition(adapter.getItemCount()-1);
//        mLayoutManager.scrollToPosition(adapter.getItemCount()-1);
    }



//    public void showItemList(){
//        LinearLayoutManager manager = new LinearLayoutManager(MainActivity.this);
//        manager.setStackFromEnd(true);
//        recyclerView.setLayoutManager(manager);
//    }

}