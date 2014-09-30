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

import java.util.concurrent.TimeUnit;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class BenchRenderer implements Renderer {
    private int m_numFrames;

    public BenchRenderer(int p_numFrames) {
        m_numFrames = p_numFrames;
    }

    @Override
    public void onSurfaceCreated(GL10 p_gl, EGLConfig p_config) {
        BenchLibJniWrapper.on_surface_created();
    }

    @Override
    public void onSurfaceChanged(GL10 p_gl, int p_width, int p_height) {
        BenchLibJniWrapper.on_surface_changed(p_width, p_height);
    }

    @Override
    public void onDrawFrame(GL10 p_gl) {
        if(m_numFrames!=0) {
            long startNanoSec = System.nanoTime();

            BenchLibJniWrapper.on_draw_frame();

            long stopNanoSec = System.nanoTime();
            double elapsedMilliSec = (double)(stopNanoSec - startNanoSec) / 1000000.0;
            Log.d("dv2524", "Frametime: " + String.valueOf(elapsedMilliSec));

            m_numFrames--;
        } else {
            System.exit(0);
        }
    }
}