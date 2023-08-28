package com.ygh547.matchrun.model;


import android.widget.Spinner;

import java.io.Serializable;

public class User2 {

    private String email;
    private String password;
    private String subEmail;
    private Spinner question;
    private String questionAn;
    private String name;
    private String nickname;
    private String address;
    private String addrDetail;


    public User2(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public User2(String email, String password, String name) {
        this.email = email;
        this.password = password;
        this.name = name;

    }

    public User2(String name, String subemail, Spinner question, String questionAn) {
        this.name = name;
        this.subEmail = subemail;
        this.question = question;
        this.questionAn = questionAn;
    }

    public User2(String email, Spinner question2, String questionAn2) {
        this.email = email;
        this.question = question2;
        this.questionAn = questionAn2;
    }


    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getSubEmail() {
        return subEmail;
    }

    public void setSubEmail(String subEmail) {
        this.subEmail = subEmail;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Spinner getQuestion() {
        return question;
    }

    public void setQuestion(Spinner question) {
        this.question = question;
    }

    public String getQuestionAn() {
        return questionAn;
    }

    public void setQuestionAn(String questionAn) {
        this.questionAn = questionAn;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddrDetail() {
        return addrDetail;
    }

    public void setAddrDetail(String addrDetail) {
        this.addrDetail = addrDetail;
    }
}
