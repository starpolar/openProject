package com.ygh547.matchrun.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.ygh547.matchrun.R;
import com.ygh547.matchrun.model.ChatData;

import java.util.List;

public class ChatAdapter extends RecyclerView.Adapter<ChatAdapter.MyViewHolder> {
    private List<ChatData> mDataset;
    private String myNickName;

    public static class MyViewHolder extends RecyclerView.ViewHolder {
        public TextView TextViewNickName;
        public TextView TextViewMsg;
        public View rootView;
        public MyViewHolder(View itemView) {
            super(itemView);
            TextViewNickName = itemView.findViewById(R.id.editNick);
            TextViewMsg = itemView.findViewById(R.id.editMsg);
            rootView = itemView;
        }
    }

    public ChatAdapter(List<ChatData> myDataset, Context context, String myNickName) {
        mDataset = myDataset;
        this.myNickName = myNickName;
    }

    @Override
    public ChatAdapter.MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LinearLayout v = (LinearLayout) LayoutInflater.from(parent.getContext()).inflate(R.layout.row_chat, parent, false);

        MyViewHolder vh = new MyViewHolder(v);
        return vh;
    }

    @Override
    public void onBindViewHolder(@NonNull ChatAdapter.MyViewHolder holder, int position) {
        ChatData chat = mDataset.get(position);

        holder.TextViewNickName.setText(chat.getNickName());
        holder.TextViewMsg.setText(chat.getMsg());

        if(chat.getNickName().equals(this.myNickName)){
            holder.TextViewNickName.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_END);
            holder.TextViewMsg.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_END);
        } else{
            holder.TextViewNickName.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_START);
            holder.TextViewMsg.setTextAlignment(View.TEXT_ALIGNMENT_VIEW_START);
        }
    }

    @Override
    public int getItemCount() {
        return mDataset == null ? 0 : mDataset.size();
    }

    public ChatData getChat(int position){
        return mDataset != null ? mDataset.get(position) : null ;
    }

    public void addChat(ChatData chat) {
        mDataset.add(chat);
        notifyItemInserted(mDataset.size()-1); // 갱신
    }


}
