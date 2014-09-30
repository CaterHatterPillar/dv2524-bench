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

// Corresponds to Enum specified in BenchGl.h.
public enum SCENE {
    SCENE_Julia(0),
    SCENE_Phong(1),
    SCENE_Chess(2),

    SCENE_Last(3); // Update me if you're adding scenes!

    public int toInt() {
        return this.m_val;
    }

    private final int m_val;
    private SCENE(int p_val) {
        this.m_val = p_val;
    }
}
