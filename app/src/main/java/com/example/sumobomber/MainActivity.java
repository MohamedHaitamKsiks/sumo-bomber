package com.example.sumobomber;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.View;

import com.google.androidgamesdk.GameActivity;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Vector;

public class MainActivity extends GameActivity {
    static {
        System.loadLibrary("sumobomber");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        try {
            Vector<Float> values = new Vector<>();
            AssetManager assetManager = getAssets();
            //InputStream inputStream = assetManager.open("data_sound_1am.bin");
            InputStream inputStream = assetManager.open("sound/circus.wav");
            byte[] buffer = new byte[2];
            DataInputStream dataInputStream = new DataInputStream(inputStream);

            dataInputStream.skip(44);

            int j=0;
            while (dataInputStream.read(buffer) == 2) {
                //float value = ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getFloat();

                short valueTest = ByteBuffer.wrap(buffer).order(ByteOrder.LITTLE_ENDIAN).getShort();

                if(j==44100*2*60){break;}

                float floatValue = (float) valueTest / 32768.0f;  // Convert short value to float in the range [-1.0, 1.0]

                values.add(floatValue);
                //values.add(value);
                //Log.d("FileReader", String.valueOf(value));
                j+=1;
            }
            float[] floatArray = new float[values.size()];
            for (int i = 0; i < values.size(); i++) {
                floatArray[i] = values.get(i);
            }
            VectorFromJNI(floatArray);
            dataInputStream.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

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
    public native int VectorFromJNI(float[] vector);
}