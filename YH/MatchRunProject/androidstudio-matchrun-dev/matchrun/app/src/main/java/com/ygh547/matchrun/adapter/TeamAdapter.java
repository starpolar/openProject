package com.ygh547.matchrun.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.ygh547.matchrun.R;
import com.ygh547.matchrun.model.Team;

import java.util.List;

public class TeamAdapter extends RecyclerView.Adapter<TeamAdapter.ViewHolder> {

    Context context;
    List<Team> teamList;

    public TeamAdapter(Context context, List<Team> teamList) {
        this.context = context;
        this.teamList = teamList;
    }

    @NonNull
    @Override
    public TeamAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.team_row, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull TeamAdapter.ViewHolder holder, int position) {
        Team team = teamList.get(position);
        holder.txtname.setText(team.name);
        holder.txtcon.setText(team.Context);
        holder.editnumber.setText(team.number);

        Glide.with(context).load(team.imgUrl).into(holder.imgteam);



    }

    @Override
    public int getItemCount() {
        return teamList.size();
    }
    public class ViewHolder extends RecyclerView.ViewHolder{

        ImageView imgteam;
        TextView txtname;
        TextView txtcon;
        EditText editnumber;
        CardView cardView;


        public ViewHolder(@NonNull View itemView) {
            super(itemView);

            imgteam = itemView.findViewById(R.id.imgteam);
            txtname = itemView.findViewById(R.id.txtname);
            txtcon = itemView.findViewById(R.id.txtCon);
            editnumber = itemView.findViewById(R.id.editnumber);
            cardView = itemView.findViewById(R.id.cardView);

            imgteam.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                }
            });

            cardView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    int index = getAdapterPosition();
                    Team team = teamList.get(index);

                }
            });

        }
    }

}
