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

#ifndef DV2524_SCENE_H
#define DV2524_SCENE_H

#include "math.h"
#include "util.h"
#include "timer.h"
#include "common.h"
#include "utilgl.h"
#include "glwrapper.h"

typedef struct Scene {
    GLuint winWidth;
    GLuint winHeight;

    void* data;
} Scene;

int sceneJuliaOnCreated(Scene* io_scene);
void sceneJuliaOnChanged(Scene* io_scene, int p_width, int p_height);
void sceneJuliaOnDraw(Scene* io_scene);
void sceneJuliaOnDestroy(Scene* io_scene);

int scenePhongOnCreated(Scene* io_scene);
void scenePhongOnChanged(Scene* io_scene, int p_width, int p_height);
void scenePhongOnDraw(Scene* io_scene);
void scenePhongOnDestroy(Scene* io_scene);

int sceneChessOnCreated(Scene* io_scene);
void sceneChessOnChanged(Scene* io_scene, int p_width, int p_height);
void sceneChessOnDraw(Scene* io_scene);
void sceneChessOnDestroy(Scene* io_scene);

#endif // DV2524_SCENE_H
