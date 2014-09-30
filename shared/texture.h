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

#ifndef DV2524_TEXTURE_H
#define DV2524_TEXTURE_H

#include "glwrapper.h"

typedef struct texture_t {
    GLuint width;
    GLuint height;
    GLuint bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    GLbyte pixel_data[2048 * 2048 * 3 + 1];
} texture_t;

#endif // DV2524_TEXTURE_H