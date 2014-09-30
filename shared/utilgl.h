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

#ifndef DV2524_BENCH_UTILGL_H
#define DV2524_BENCH_UTILGL_H

#include "glwrapper.h"

GLint utilGlCreateShader(
    GLuint* io_shaderId,
    GLenum p_shaderType,
    const char* p_shaderSrc);

GLuint utilGlCreateTexture(
    GLsizei p_width,
    GLsizei p_height,
    GLint p_format,
    GLenum p_type,
    const GLvoid* p_texels);
void utilGlUpdateTexture(
    GLuint p_texId,
    GLsizei p_width,
    GLsizei p_height,
    GLint p_format,
    GLenum p_type,
    const GLvoid* p_texels);

#endif // DV2524_BENCH_UTILGL_H
