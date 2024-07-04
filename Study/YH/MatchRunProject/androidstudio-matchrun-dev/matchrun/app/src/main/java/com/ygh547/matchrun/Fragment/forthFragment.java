package com.ygh547.matchrun.Fragment;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.ygh547.matchrun.R;
import com.ygh547.matchrun.adapter.ChatAdapter;
import com.ygh547.matchrun.model.ChatData;
import com.ygh547.matchrun.model.User2;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link forthFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class forthFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    private RecyclerView recyclerView;
    public RecyclerView.Adapter adapter;
    private RecyclerView.LayoutManager mLayoutManager;
    private List<ChatData> chatList;
    private String nick = "nick2";

//    private String nick2 = new User2(getActivity().getLocalClassName()).getNickname();

    private EditText editChat;
    private Button btnSend;
    private DatabaseReference myRef;

    private Activity activity;

    public forthFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment forthFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static forthFragment newInstance(String param1, String param2) {
        forthFragment fragment = new forthFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }

    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_forth, container, false);
        getActivity().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_PAN);
        recyclerView = rootView.findViewById(R.id.recyclerView);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity().getApplicationContext()));

        chatList = new ArrayList<>();
        adapter = new ChatAdapter(chatList, getActivity().getApplicationContext(), nick);
        recyclerView.setAdapter(adapter);

        btnSend = rootView.findViewById(R.id.btnSend);
        editChat = rootView.findViewById(R.id.editChat);

        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String msg = editChat.getText().toString();

                if(msg != null){
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
        return rootView;
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
