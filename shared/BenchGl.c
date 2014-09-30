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

#include "BenchGl.h"
#include "glwrapper.h"

static Benchmark s_benchmark;

void on_init(SCENE p_scene) {
    memset(&s_benchmark, 0, sizeof(Benchmark));
    s_benchmark.scene = p_scene;
}

int on_surface_created() {
    int ret = -1;
    Scene* scene = &s_benchmark.scenes[ s_benchmark.scene ];
    switch(s_benchmark.scene) {
    case SCENE_Julia:
        ret = sceneJuliaOnCreated(scene);
        break;
    case SCENE_Phong:
        ret = scenePhongOnCreated(scene);
        break;
    case SCENE_Chess:
        ret = sceneChessOnCreated(scene);
        break;
    default:
        break;
    }
    return ret;
}

void on_surface_changed(int p_width, int p_height) {
    Scene* scene = &s_benchmark.scenes[ s_benchmark.scene ];
    switch(s_benchmark.scene) {
    case SCENE_Julia:
        sceneJuliaOnChanged(scene, p_width, p_height);
        break;
    case SCENE_Phong:
        scenePhongOnChanged(scene, p_width, p_height);
        break;
    case SCENE_Chess:
        sceneChessOnChanged(scene, p_width, p_height);
        break;
    default:
        break;
    }
}

void on_draw_frame() {
    Scene* scene = &s_benchmark.scenes[ s_benchmark.scene ];
    switch(s_benchmark.scene) {
    case SCENE_Julia:
        sceneJuliaOnDraw(scene);
        break;
    case SCENE_Phong:
        scenePhongOnDraw(scene);
        break;
    case SCENE_Chess:
        sceneChessOnDraw(scene);
        break;
    default:
        break;
    }
}

void on_destroy() {
    Scene* scene = &s_benchmark.scenes[ s_benchmark.scene ];
    switch(s_benchmark.scene) {
    case SCENE_Julia:
        sceneJuliaOnDestroy(scene);
        break;
    case SCENE_Phong:
        scenePhongOnDestroy(scene);
        break;
    case SCENE_Chess:
        sceneChessOnDestroy(scene);
        break;
    default:
        break;
    }
}
