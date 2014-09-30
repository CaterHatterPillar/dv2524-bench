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

#ifndef DV2524_BENCH_BENCHGL_H_
#define DV2524_BENCH_BENCHGL_H_

#include "util.h"
#include "scene.h"
#include "config.h"

// Corresponds to Enum specified in SCENE.java.
typedef enum {
    SCENE_Julia = 0,
    SCENE_Phong = 1,
    SCENE_Chess = 2,

    SCENE_Num,
    SCENE_Invalid
} SCENE;

void on_init(SCENE p_scene);
int on_surface_created();
void on_surface_changed(int p_width, int p_height);
void on_draw_frame();
void on_destroy();

typedef struct Benchmark {
    SCENE scene;
    Scene scenes[ SCENE_Num ]; // Not actually being utilized. Consider removing.
} Benchmark;

#endif /* DV2524_BENCH_BENCHGL_H_ */
