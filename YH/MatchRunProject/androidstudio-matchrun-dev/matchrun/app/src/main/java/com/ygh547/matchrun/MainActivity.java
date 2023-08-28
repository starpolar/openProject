package com.ygh547.matchrun;

import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.bottomnavigation.BottomNavigationMenuView;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationBarView;
import com.ygh547.matchrun.Fragment.fifthFragment;
import com.ygh547.matchrun.Fragment.firstFragment;
import com.ygh547.matchrun.Fragment.forthFragment;
import com.ygh547.matchrun.Fragment.secondFragment;
import com.ygh547.matchrun.Fragment.thirdFragment;

public class MainActivity extends AppCompatActivity {

    RecyclerView recyclerView;
    TextView txtmyTeam;
    BottomNavigationMenuView Smenu;
    ImageView imgPlus;
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
        setContentView(R.layout.activity_main);

        bottomNavigation = findViewById(R.id.bottomNavigation);

        firstFragment = new firstFragment();
        secondFragment = new secondFragment();
        thirdFragment = new thirdFragment();
        forthFragment = new forthFragment();
        fifthFragment = new fifthFragment();

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
//                Intent intent = new Intent(MainActivity.this,firstFragment.class);
                FragmentManager fragmentManager = getSupportFragmentManager();
                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                fragmentTransaction.replace(R.id.fragment, thirdFragment);
                fragmentTransaction.commit();


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

//    public void replaceFragment(Fragment fragment){
//        FragmentManager fragmentManager = getSupportFragmentManager();
//        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
//        fragmentTransaction.replace(R.id.fragment, thirdFragment);
//        fragmentTransaction.commit();
//    }
}

