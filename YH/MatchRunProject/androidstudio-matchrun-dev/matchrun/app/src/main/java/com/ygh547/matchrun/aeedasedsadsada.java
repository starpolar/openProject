//package com.ygh547.matchrun;
//
//import androidx.appcompat.app.AppCompatActivity;
//
//import android.os.Bundle;
//
//public class aeedasedsadsada extends AppCompatActivity {
//            implements GoogleApiClient.OnConnectionFailedListener,View.OnClickListener {
//    private static final String TAG = "MainActivity";
//
//    EditText edit_id, edit_password;
//    TextView txt_id, txt_password, txt_register;
//    SignInButton signBt;
//    Button btnlogin, logoutBt, btn_revoke;
//
//    private static final int RC_SIGN_IN = 1000;
//    private FirebaseAuth mAuth;
//    private GoogleApiClient mGoogleApiClient;
//    private static final int REQ_ONE_TAP = 2;  // Can be any integer unique to the Activity.
//    private boolean showOneTapUI = true;
//    private SignInClient oneTapClient;
//    private GoogleSignInClient mGoogleSignInClient;
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//    }
//}
//
//        edit_id = findViewById(R.id.edit_email);
//        edit_password = findViewById(R.id.edit_password);
//        txt_id = findViewById(R.id.edit_email);
//        txt_password = findViewById(R.id.txt_password);
//        txt_register = findViewById(R.id.txt_register);
//        btnlogin = findViewById(R.id.imglogin);
//        btn_revoke = findViewById(R.id.btn_revoke);
//
//        signBt = findViewById(R.id.signBt);
//        signBt.setOnClickListener(this);
//        logoutBt = findViewById(R.id.logoutBt);
//        logoutBt.setOnClickListener(this);
//
//
//        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
//                .requestIdToken(getString(R.string.default_web_client_id))
//                .requestEmail()
//                .build();
//
//
//        mGoogleApiClient = new GoogleApiClient.Builder(this)
//                .enableAutoManage(this, this)
//                .addApi(Auth.GOOGLE_SIGN_IN_API,gso)
//                .build();
//
//        mAuth = FirebaseAuth.getInstance();
//
//        getHashKey();
//
//        // 기존에 로그인 했던 계정을 확인한다.
//        GoogleSignInAccount gsa = GoogleSignIn.getLastSignedInAccount(MainActivity.this);
//
//        // 로그인 되있는 경우 (토큰으로 로그인 처리)
//        if (gsa != null && gsa.getId() != null) {
//
//        }
//
//    }
//
//    @Override
//    public void onActivityResult(int requestCode, int resultCode, Intent data) {
//        super.onActivityResult(requestCode, resultCode, data);
//
//        if (requestCode == RC_SIGN_IN) {
//            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
//            handleSignInResult(task);
//
//            GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
//            if (result.isSuccess()) {
//                GoogleSignInAccount account = result.getSignInAccount();
//                firebaseAuthWithGoogle(account);
//            } else {
//            }
//        }
//    }
//
//    @Override
//    public void onClick(View v) {
//        switch (v.getId()) {
//            case R.id.signBt:
//                Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
//                startActivityForResult(signInIntent,RC_SIGN_IN);
//                break;
//            case R.id.logoutBt:
//
//
//
//        }
//    }
//
//
//        Google_Login = findViewById(R.id.signBt);
//        Google_Login.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
//                startActivityForResult(signInIntent,RC_SIGN_IN);
//            }
//        });
//
//        google_LogoutBt = findViewById(R.id.logoutBt);
//        google_LogoutBt.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                mGoogleSignInClient.signOut()
//                        .addOnCompleteListener(this, task -> {
//                            Log.d(TAG, "onClick:logout success ");
//                            mGoogleSignInClient.revokeAccess()
//                                    .addOnCompleteListener(this, task1 -> Log.d(TAG, "onClick:revokeAccess success "));
//            }
//        });
//    }
//
//
//    private void handleSignInResult(Task<GoogleSignInAccount> completedTask) {
//        try {
//            GoogleSignInAccount acct = completedTask.getResult(ApiException.class);
//
//            if (acct != null) {
//                String personName = acct.getDisplayName();
//                String personGivenName = acct.getGivenName();
//                String personFamilyName = acct.getFamilyName();
//                String personEmail = acct.getEmail();
//                String personId = acct.getId();
//                Uri personPhoto = acct.getPhotoUrl();
//
//                Log.d(TAG, "handleSignInResult:personName " + personName);
//                Log.d(TAG, "handleSignInResult:personGivenName " + personGivenName);
//                Log.d(TAG, "handleSignInResult:personEmail " + personEmail);
//                Log.d(TAG, "handleSignInResult:personId " + personId);
//                Log.d(TAG, "handleSignInResult:personFamilyName " + personFamilyName);
//                Log.d(TAG, "handleSignInResult:personPhoto " + personPhoto);
//            }
//        } catch (ApiException e) {
//            // The ApiException status code indicates the detailed failure reason.
//            // Please refer to the GoogleSignInStatusCodes class reference for more information.
//            Log.e(TAG, "signInResult:failed code=" + e.getStatusCode());
//
//        }
//    }
//
//
//    private void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
//        AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
//        mAuth.signInWithCredential(credential)
//                .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
//                    @Override
//                    public void onComplete(@NonNull Task<AuthResult> task) {
//                        if (!task.isSuccessful()) {
//                            Toast.makeText(MainActivity.this, "인증 실패", Toast.LENGTH_SHORT).show();
//                        } else {
//                            Toast.makeText(MainActivity.this, "구글 로그인 인증 성공", Toast.LENGTH_SHORT).show();
//                        }
//                    }
//                });
//    }
//
//    private void getHashKey() {
//        PackageInfo packageInfo = null;
//        try {
//            packageInfo = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_SIGNATURES);
//        } catch (PackageManager.NameNotFoundException e) {
//            e.printStackTrace();
//        }
//        if (packageInfo == null)
//            Log.e("KeyHash", "KeyHash:null");
//
//        for (Signature signature : packageInfo.signatures) {
//            try {
//                MessageDigest md = MessageDigest.getInstance("SHA");
//                md.update(signature.toByteArray());
//                Log.d("KeyHash", Base64.encodeToString(md.digest(), Base64.DEFAULT));
//            } catch (NoSuchAlgorithmException e) {
//                Log.e("KeyHash", "Unable to get MessageDigest. signature=" + signature, e);
//            }
//        }
//    }
//
//
//    @Override
//    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
//
//    }
//}