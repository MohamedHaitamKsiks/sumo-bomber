package com.example.sumobomber;
import android.content.Context;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Loader {
    /**
     * Returns the list of internal storage paths.
     */
    public static ArrayList<String> copyAssetsToInternalStorage(
            Context context,
            List<String> assetsFilePaths) {
        android.content.res.AssetManager assetManager = context.getApplicationContext().getAssets();
        String internalStorageFilesDirAbsolutePath = context.getFilesDir().getAbsolutePath();
        ArrayList<String> result = new ArrayList<>();

        for (String assetsFilePath : assetsFilePaths) {
            InputStream inputStream = null;
            OutputStream outputStream = null;
            try {
                File outFile = new File(internalStorageFilesDirAbsolutePath, assetsFilePath);
                result.add(outFile.getAbsolutePath());
                if (!outFile.exists()) {
                    File file = outFile.getParentFile();
                    if (!file.exists()) {
                        file.mkdirs();
                    }
                    inputStream = assetManager.open(assetsFilePath);
                    outputStream = new FileOutputStream(outFile);
                    copyFile(inputStream, outputStream);
                }
            } catch (IOException e) {
                throw new IllegalStateException("Failed to copy asset file: " + assetsFilePath, e);
            } finally {
                try {
                    if (inputStream != null) {
                        inputStream.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {
                    if (outputStream != null) {
                        outputStream.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return result;
    }

    /**
     * Returns the list of internal storage paths.
     */
    public static String copyAssetToInternalStorage(
            Context context,
            String assetsFilePath) {
        android.content.res.AssetManager assetManager = context.getApplicationContext().getAssets();
        String internalStorageFilesDirAbsolutePath = context.getFilesDir().getAbsolutePath();
        String result;

        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            File outFile = new File(internalStorageFilesDirAbsolutePath, assetsFilePath);
            result = outFile.getAbsolutePath();
            if (!outFile.exists()) {
                File file = outFile.getParentFile();
                if (!file.exists()) {
                    file.mkdirs();
                }
                inputStream = assetManager.open(assetsFilePath);
                outputStream = new FileOutputStream(outFile);
                copyFile(inputStream, outputStream);
            }
        } catch (IOException e) {
            throw new IllegalStateException("Failed to copy asset file: " + assetsFilePath, e);
        } finally {
            try {
                if (inputStream != null) {
                    inputStream.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                if (outputStream != null) {
                    outputStream.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return result;
    }

    private static void copyFile(InputStream inputStream, OutputStream out) {
        byte[] buffer = new byte[1024];
        while (true) {
            try {
                int bytesRead = inputStream.read(buffer);
                if (bytesRead == -1) {
                    break;
                }
                out.write(buffer, 0, bytesRead);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

