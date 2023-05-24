package com.example.sumobomber;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import com.google.androidgamesdk.GameActivity;
import com.example.sumobomber.AudioEngineBridge;
public class MainActivity extends GameActivity {
    static {
        System.loadLibrary("sumobomber");
    }

    private AudioEngineBridge jniBridge;
    private AudioEngineBridge jniBridge2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        jniBridge=new AudioEngineBridge();
        jniBridge2=new AudioEngineBridge();
        jniBridge.loadFromAssets(this, "audio/circus.wav");
        jniBridge2.loadFromAssets2(this, "audio/test.wav");
        //jniBridge.play(0);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        if (hasFocus) {
            hideSystemUi();
        }
    }

    private void hideSystemUi() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN
        );
    }
}