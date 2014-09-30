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

public class BenchLibJniWrapper {
    static {
        System.loadLibrary("bench");
    }

    public static native void on_init(int scene);
    public static native int on_surface_created();
    public static native void on_surface_changed(int width, int height);
    public static native void on_draw_frame();
    public static native void on_destroy();
}
