package com.ygh547.matchrun.login;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.net.Uri;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.util.Patterns;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.identity.SignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthCredential;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.GetTokenResult;
import com.google.firebase.auth.GoogleAuthProvider;
import com.kakao.sdk.auth.model.OAuthToken;
import com.kakao.sdk.common.model.AuthErrorCause;
import com.kakao.sdk.common.util.Utility;
import com.kakao.sdk.user.UserApiClient;
import com.kakao.sdk.user.model.AccessTokenInfo;
import com.kakao.sdk.user.model.Account;
import com.ygh547.matchrun.ChatActivity;
import com.ygh547.matchrun.Fragment.forthFragment;
import com.ygh547.matchrun.MainActivity;
import com.ygh547.matchrun.R;
import com.ygh547.matchrun.api.NetworkClient;
import com.ygh547.matchrun.api.UserApi;
import com.ygh547.matchrun.config.Config;
import com.ygh547.matchrun.login.RegisterActivity;
import com.ygh547.matchrun.login.findidActivity;
import com.ygh547.matchrun.login.findpasswordActivity;
import com.ygh547.matchrun.model.User2;
import com.ygh547.matchrun.model.UserRes;


import org.jetbrains.annotations.Nullable;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.regex.Pattern;

import kotlin.Unit;
import kotlin.jvm.functions.Function2;
import kotlin.jvm.internal.Intrinsics;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;

public class LoginActivity extends AppCompatActivity implements GoogleApiClient.OnConnectionFailedListener {

    EditText editemail;
    EditText editpassword;
    ImageView imglogin;
    ImageView imgkakaologin;
    ImageView imggooglelogin;
    TextView txtid;
    TextView txtpassword;
    TextView txtregister;


    private static final int RC_SIGN_IN = 1000;
    private FirebaseAuth mAuth;
    private GoogleApiClient mGoogleApiClient;
    private static final int REQ_ONE_TAP = 2;  // Can be any integer unique to the Activity.
    private boolean showOneTapUI = true;
    private SignInClient oneTapClient;
    private GoogleSignInClient mGoogleSignInClient;
    private ProgressDialog dialog;
    private static final String TAG = "TAG";




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        editemail = findViewById(R.id.editemail2);
        editpassword = findViewById(R.id.editpassword);
        imglogin = findViewById(R.id.imglogin);
        txtid = findViewById(R.id.txtid);
        txtpassword = findViewById(R.id.txtpassword);
        txtregister = findViewById(R.id.txtregister);
        imgkakaologin = findViewById(R.id.imgkakaologin);
        imggooglelogin = findViewById(R.id.imggooglelogin);


        imglogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String email = editemail.getText().toString().trim();
                Pattern pattern = Patterns.EMAIL_ADDRESS;
                if (pattern.matcher(email).matches() == false) {
                    Toast.makeText(LoginActivity.this, "로그인 정보를 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }

                String password = editpassword.getText().toString().trim();

                Retrofit retrofit = NetworkClient.getRetrofitClient(LoginActivity.this);
                UserApi api = retrofit.create(UserApi.class);

                User2 user2 = new User2(email, password);
                Call<UserRes> call = api.login2(user2);

                showProgress("로그인 중...");
                call.enqueue(new Callback<UserRes>() {
                    @Override
                    public void onResponse(Call<UserRes> call, Response<UserRes> response) {
                        dismissProgress();

                        if(response.isSuccessful()){

                            UserRes userRes = response.body();
                            String accessToken = userRes.getAccess_token();

                            SharedPreferences sp = getApplication().getSharedPreferences(Config.PREFERENCES_NAME, MODE_PRIVATE);
                            SharedPreferences.Editor editor = sp.edit();
                            editor.putString("accessToken", accessToken);
                            editor.apply();

                            Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                            startActivity(intent);
//                            finish();


                        } else {
                            Toast.makeText(LoginActivity.this, "회원정보가 없습니다.", Toast.LENGTH_SHORT).show();

                        }

                    }

                    @Override
                    public void onFailure(Call<UserRes> call, Throwable t) {
                        dismissProgress();
                    }
                });


            }
        });

        txtid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this, findidActivity.class);
                startActivity(intent);
//                finish();
            }
        });

        txtpassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this, findpasswordActivity.class);
                startActivity(intent);
//                finish();
            }
        });

        txtregister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this, RegisterActivity.class);
                startActivity(intent);
//                finish();
            }
        });

        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(getString(R.string.default_web_client_id))
                .requestEmail()
                .build();

        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .enableAutoManage(this, this)
                .addApi(Auth.GOOGLE_SIGN_IN_API, gso)
                .build();

        mAuth = FirebaseAuth.getInstance();

        GoogleSignInAccount gsa = GoogleSignIn.getLastSignedInAccount(LoginActivity.this);

        // 로그인 되있는 경우 (토큰으로 로그인 처리)
        if (gsa != null && gsa.getId() != null) {
            Intent intent = new Intent(LoginActivity.this, MainActivity.class);
            startActivity(intent);
        }

        FirebaseUser mUser = FirebaseAuth.getInstance().getCurrentUser();
//        mUser.getIdToken(true)
//                .addOnCompleteListener(new OnCompleteListener<GetTokenResult>() {
//                    public void onComplete(@NonNull Task<GetTokenResult> task) {
//                        if (task.isSuccessful()) {
//                            String idToken = task.getResult().getToken();
//                            // Send token to your backend via HTTPS
//                            Log.d("qwe",""+idToken);
//                        } else {
//                            // Handle error -> task.getException();
//                        }
//                    }
//                });

        UserApiClient.Companion.getInstance().accessTokenInfo((Function2)(new Function2() {
            // $FF: synthetic method
            // $FF: bridge method
            public Object invoke(Object var1, Object var2) {
                this.invoke((AccessTokenInfo)var1, (Throwable)var2);
                return Unit.INSTANCE;
            }

            public final void invoke(@Nullable AccessTokenInfo tokenn, @Nullable Throwable error) {
                Log.d("Mytest2", String.valueOf(tokenn));
                if (error != null) {
                    Log.d("토큰", "" + tokenn);
                } else if (tokenn != null) {
//                    Toast.makeText(LoginActivity.this,"토큰 정보 보기 성공",Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                    LoginActivity.this.startActivity(intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
                    LoginActivity.this.finish();
                }

            }
        }));
        String keyHash = Utility.INSTANCE.getKeyHash((Context)this);
        Log.d("Hash", keyHash);
        final Function2 callback = (Function2)(new Function2() {
            // $FF: synthetic method
            // $FF: bridge method
            public Object invoke(Object var1, Object var2) {
                this.invoke((OAuthToken)var1, (Throwable)var2);
                return Unit.INSTANCE;
            }
            public final void invoke(@Nullable OAuthToken token, @Nullable Throwable error) {
                Log.d("Mytest", String.valueOf(token));
                if (error != null) {
                    if (Intrinsics.areEqual(error.toString(), AuthErrorCause.AccessDenied.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"접근이 거부 됨(동의 취소)", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.InvalidClient.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"유효하지 않은 앱", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.InvalidGrant.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"인증 수단이 유효하지 않아 인증할 수 없는 상태", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.InvalidRequest.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"요청 파라미터 오류", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.InvalidScope.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"유효하지 않은 scope ID", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.Misconfigured.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"설정이 올바르지 않음(android key hash)", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.ServerError.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"서버 내부 에러", Toast.LENGTH_SHORT).show();
                    } else if (Intrinsics.areEqual(error.toString(), AuthErrorCause.Unauthorized.toString())) {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"앱이 요청 권한이 없음", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText((Context)LoginActivity.this, (CharSequence)"기타 에러", Toast.LENGTH_SHORT).show();
                    }
                } else if (token != null) {
                    Toast.makeText((Context)LoginActivity.this, (CharSequence)"로그인에 성공하였습니다.", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent((Context)LoginActivity.this, MainActivity.class);
                    startActivity(intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
                    finish();
                }

            }
        });

        imggooglelogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
                startActivityForResult(signInIntent, RC_SIGN_IN);


                Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });

        getHashKey();


        imgkakaologin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(UserApiClient.getInstance().isKakaoTalkLoginAvailable(LoginActivity.this)){
                    login();
                    Intent intent2 = new Intent(LoginActivity.this, MainActivity.class);
//                    startActivity(intent2);
                }
                else{
                    accountLogin();
                }

            }
        });
    }

    public void login(){
        String TAG = "login()";
        UserApiClient.getInstance().loginWithKakaoTalk(LoginActivity.this,(oAuthToken, error) -> {
            if (error != null) {
                Log.e(TAG, "로그인 실패", error);
            } else if (oAuthToken != null) {
                Log.i(TAG, "로그인 성공(토큰) : " + oAuthToken.getAccessToken());
                getUserInfo();
            }
            return null;
        });
    }

    public void accountLogin(){
        String TAG = "accountLogin()";
        UserApiClient.getInstance().loginWithKakaoAccount(LoginActivity.this,(oAuthToken, error) -> {
            if (error != null) {
                Log.e(TAG, "로그인 실패", error);
            } else if (oAuthToken != null) {
                Log.i(TAG, "로그인 성공(토큰) : " + oAuthToken.getAccessToken());
                getUserInfo();
            }
            return null;
        });
    }

    public void getUserInfo(){
        String TAG = "getUserInfo()";
        UserApiClient.getInstance().me((user, meError) -> {
            if (meError != null) {
                Log.e(TAG, "사용자 정보 요청 실패", meError);
            } else {
                System.out.println("로그인 완료");
                Log.i(TAG, user.toString());
                {
                    Log.i(TAG, "사용자 정보 요청 성공" +
                            "\n회원번호: "+user.getId() +
                            "\n이메일: "+user.getKakaoAccount().getEmail());
                }
                Account user1 = user.getKakaoAccount();
                System.out.println("사용자 계정" + user1);
            }
            return null;
        });
    }





    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RC_SIGN_IN) {
            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
            handleSignInResult(task);

            GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
            if (result.isSuccess()) {
                GoogleSignInAccount account = result.getSignInAccount();
                firebaseAuthWithGoogle(account);
            } else {
            }
        }
    }

    private void handleSignInResult(Task<GoogleSignInAccount> completedTask) {
        try {
            GoogleSignInAccount acct = completedTask.getResult(ApiException.class);

            if (acct != null) {
                String personName = acct.getDisplayName();
                String personGivenName = acct.getGivenName();
                String personFamilyName = acct.getFamilyName();
                String personEmail = acct.getEmail();
                String personId = acct.getId();
                Uri personPhoto = acct.getPhotoUrl();

                Log.d(TAG, "handleSignInResult:personName " + personName);
                Log.d(TAG, "handleSignInResult:personGivenName " + personGivenName);
                Log.d(TAG, "handleSignInResult:personEmail " + personEmail);
                Log.d(TAG, "handleSignInResult:personId " + personId);
                Log.d(TAG, "handleSignInResult:personFamilyName " + personFamilyName);
                Log.d(TAG, "handleSignInResult:personPhoto " + personPhoto);
            }
        } catch (ApiException e) {
            // The ApiException status code indicates the detailed failure reason.
            // Please refer to the GoogleSignInStatusCodes class reference for more information.
            Log.e(TAG, "signInResult:failed code=" + e.getStatusCode());

        }
    }

    private void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
        AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
        mAuth.signInWithCredential(credential)
                .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if (!task.isSuccessful()) {
                            Toast.makeText(LoginActivity.this, "인증 실패", Toast.LENGTH_SHORT).show();
                        } else {
                            Toast.makeText(LoginActivity.this, "구글 로그인 인증 성공", Toast.LENGTH_SHORT).show();
                        }
                    }
                });
    }


    private void getHashKey(){
        PackageInfo packageInfo = null;
        try {
            packageInfo = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_SIGNATURES);
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        if (packageInfo == null)
            Log.e("KeyHash", "KeyHash:null");

        for (Signature signature : packageInfo.signatures) {
            try {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                Log.d("KeyHash", Base64.encodeToString(md.digest(), Base64.DEFAULT));
            } catch (NoSuchAlgorithmException e) {
                Log.d("KeyHash", "해시 키 오류 : " + signature, e);
            }
        }
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


    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {

    }
}
