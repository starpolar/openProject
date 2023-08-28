package com.ygh547.matchrun;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationBarView;
import com.ygh547.matchrun.Fragment.fifthFragment;
import com.ygh547.matchrun.Fragment.firstFragment;
import com.ygh547.matchrun.Fragment.forthFragment;
import com.ygh547.matchrun.Fragment.secondFragment;
import com.ygh547.matchrun.Fragment.thirdFragment;

import java.util.ArrayList;

public class TeamRegisterActivity extends AppCompatActivity {

    ImageView imgMain;
    Spinner spinner4;
    ArrayList<String> arrayList3;
    ArrayAdapter<String> arrayAdapter3;
    EditText editTeamname;
    EditText editConText;
    Button btnCh;
    Button btnRe;

    FloatingActionButton fab;

    BottomNavigationView bottomNavigation;
    Fragment firstFragment;
    Fragment secondFragment;
    Fragment thirdFragment;
    Fragment forthFragment;
    Fragment fifthFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_team_register);

        imgMain = findViewById(R.id.imgMain);
        spinner4 = findViewById(R.id.spinner4);
        editTeamname = findViewById(R.id.editTeamname);
        editConText = findViewById(R.id.editConText);
        btnCh = findViewById(R.id.btnCh);
        btnRe = findViewById(R.id.btnRe);

        bottomNavigation = findViewById(R.id.bottomNavigation);

        firstFragment = new firstFragment();
        secondFragment = new secondFragment();
        thirdFragment = new thirdFragment();
        forthFragment = new forthFragment();
        fifthFragment = new fifthFragment();

        arrayList3 = new ArrayList<>();
        arrayList3.add("종목을 선택해 주세요.");
        arrayList3.add("축구");
        arrayList3.add("야구");
        arrayList3.add("농구");
        arrayList3.add("배드민턴");


        arrayAdapter3 = new ArrayAdapter<>(getApplicationContext(),
                android.R.layout.simple_spinner_dropdown_item,
                arrayList3);

        spinner4 = (Spinner)findViewById(R.id.spinner4);
        spinner4.setAdapter(arrayAdapter3);
        spinner4.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
//                Toast.makeText(getApplicationContext(),arrayList.get(i)+"가 선택되었습니다.",
//                        Toast.LENGTH_SHORT).show();
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }
        });

        bottomNavigation.setOnItemSelectedListener(new NavigationBarView.OnItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {

                int itemId = item.getItemId();

                Fragment fragment = null;

                if(itemId ==R.id.firstFragment){
                    fragment = firstFragment;
                }else if(itemId == R.id.secondFragment){
                    fragment = secondFragment;
                }else if(itemId == R.id.thirdFragment){
                    fragment = thirdFragment;
                }else if(itemId == R.id.forthFragment){
                    fragment = forthFragment;
                }else if(itemId == R.id.fifthFragment){
                    fragment = fifthFragment;
                }

                return loadFragment(fragment);
            }
        });

        fab = findViewById(R.id.fab);
        fab.setColorFilter(R.color.color_main);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                Intent intent = new Intent(TeamRegisterActivity.this,firstFragment.class);
                FragmentManager fragmentManager = getSupportFragmentManager();
                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                fragmentTransaction.replace(R.id.fragment, thirdFragment);
                fragmentTransaction.commit();


            }
        });

        btnRe.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(TeamRegisterActivity.this, MainActivity.class);
            }
        });
    }

    private boolean loadFragment(Fragment fragment) {
        if(fragment != null){
            getSupportFragmentManager()
                    .beginTransaction()
                    .replace(R.id.fragment, fragment)
                    .commit();
            return true;
        }
        return false;
    }


}