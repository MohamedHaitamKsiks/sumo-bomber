package com.example.sumobomber;

import android.content.Context;
import android.media.AudioFormat;
import android.media.MediaExtractor;
import android.util.Log;

import com.example.sumobomber.Loader;

import java.util.ArrayList;
import java.util.List;

public class AudioEngineBridge {
    private native void jniLoadAndPlay(String filePath);

    private native void jniLoadAndPlay2(String filePath);

    private native void jniLoad(List<String> filePaths);
    private native void jniPlay(int id);

    private String filePath = "";
    private ArrayList<String> filePaths = new ArrayList<>();

    public void loadFromAssets(Context context, List<String> assetsFilePaths) {
        List<String> copiedFilePaths = Loader.copyAssetsToInternalStorage(context, assetsFilePaths);
        filePaths = new ArrayList<>(copiedFilePaths);
        jniLoad(copiedFilePaths);
    }

    public void loadFromAssets(Context context, String assetsFilePath) {
        String copiedFilePath = Loader.copyAssetToInternalStorage(context, assetsFilePath);
        filePath = copiedFilePath;
        logAudioFileInfo(copiedFilePath);
        jniLoadAndPlay(copiedFilePath);
    }
    public void loadFromAssets2(Context context, String assetsFilePath) {
        String copiedFilePath = Loader.copyAssetToInternalStorage(context, assetsFilePath);
        filePath = copiedFilePath;
        logAudioFileInfo(copiedFilePath);
        jniLoadAndPlay2(copiedFilePath);
    }

    public void logAudioFileInfo(String path) {
        MediaExtractor ex = new MediaExtractor();
        try {
            ex.setDataSource(path);
        } catch (Exception e) {
            e.printStackTrace();
        }

        int trackCount = ex.getTrackCount();
        Log.w(AudioEngineBridge.class.getCanonicalName(), "Audio File " + path + " has " + trackCount + " tracks:  ");
        for (int i = 0; i < trackCount; i++) {
            Log.w(AudioEngineBridge.class.getCanonicalName(), "Track: " + i + " INFO " + ex.getTrackFormat(i));
        }
    }

    public void loadFromFiles(List<String> filePaths) {
        jniLoad(filePaths);
    }

    public void play(int id) {
        jniPlay(id);
    }

    public void play(String path) {
        jniPlay(extractId(path));
    }

    private int extractId(String assetsFilePath) {
        for (int i = 0; i < filePaths.size(); i++) {
            if (filePaths.get(i).equals(assetsFilePath)) {
                return i;
            }
        }
        throw new IllegalStateException("Error, not found path: " + assetsFilePath);
    }
}

