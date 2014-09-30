/*
* OpenGL ES 2.0 Benchmarks for X11 Linux and Android platforms
* Copyright (c) 2014, Intel Corporation.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*/

package com.example.dv2524_bench_android;

import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.view.Menu;
import android.widget.Toast;

public class Dv2524_bench extends Activity {
    private GLSurfaceView m_glSurfaceView;
    private boolean m_rendererIsSet;

    @Override
    protected void onCreate(Bundle p_savedInstanceState) {
        super.onCreate(p_savedInstanceState);

        BenchLibJniWrapper.on_init(Config.g_benchmark.toInt());

        ActivityManager activityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 = configurationInfo.reqGlEsVersion>=0x20000 || isProbablyEmulator(); // configurationInfo.reqGlEsVersion>=0x20000 doesn't work whilst using emulator, hence the utility method isProbablyEmulator is used.
        if(supportsEs2) {
            m_glSurfaceView = new GLSurfaceView(this);
            if(isProbablyEmulator()) {   // Avoids crashes on startup with some emulator images.
                m_glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            }

            m_glSurfaceView.setEGLContextClientVersion(2);
            m_glSurfaceView.setRenderer(new BenchRenderer(Config.g_numFrames));
            m_rendererIsSet = true;
            setContentView(m_glSurfaceView);
        } else {
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.", Toast.LENGTH_LONG).show();
        }

        int[] max = new int[1];
        gl.glGetIntegerv(GL10.GL_MAX_TEXTURE_SIZE, max, 0);
        Toast.makeText(this,  String.valueOf(max), Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu p_menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.dv2524_bench, p_menu);
        return true;
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(m_rendererIsSet==true) {
            m_glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(m_rendererIsSet==true) {
            m_glSurfaceView.onResume();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        BenchLibJniWrapper.on_destroy();
    }

    private boolean isProbablyEmulator() {
        return Build.VERSION.SDK_INT>=Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
               && (Build.FINGERPRINT.startsWith("generic")
                   || Build.FINGERPRINT.startsWith("unknown")
                   || Build.MODEL.contains("google_sdk")
                   || Build.MODEL.contains("Emulator")
                   || Build.MODEL.contains("Android SDK built for x86"));
    }
}
