package com.ygh547.matchrun.model;

public class Team {

    public String teamId;
    public String name;
    public String Context;
    public String imgUrl;
    public String number;


    public Team(String teamId, String name, String imgUrl) {
        this.teamId = teamId;
        this.name = name;
        this.imgUrl = imgUrl;

    }

    public Team(String teamId, String name, String context, String imgUrl, String number) {
        this.teamId = teamId;
        this.name = name;
        this.Context = context;
        this.imgUrl = imgUrl;
        this.number = number;
    }
}
