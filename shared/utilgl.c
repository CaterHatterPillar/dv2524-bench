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

#include "utilgl.h"
#include "common.h"

GLint utilGlCreateShader(
    GLuint* io_shaderId,
    GLenum p_shaderType,
    const char* p_shaderSrc) {
    GLint success = GL_TRUE;
    *io_shaderId = glCreateShader(p_shaderType);
    if(*io_shaderId==0) {
        printf("utilGlCreateShader: shader creation failed!\n");
        success = GL_FALSE;
    }

    if(success==GL_TRUE) {
        glShaderSource(*io_shaderId, 1, &p_shaderSrc, NULL);
        glCompileShader(*io_shaderId);

        glGetShaderiv(*io_shaderId, GL_COMPILE_STATUS, &success);
        if(success!=GL_TRUE) {
            GLchar infoLog[ 256 ];
            GLsizei infoLen;
            glGetShaderInfoLog(*io_shaderId, 256, &infoLen, infoLog);
            printf("utilGlCreateShader: shader compilation failed! More info enclosed below:\n%s\n", infoLog);
        }
    }
    return success;
}

GLuint utilGlCreateTexture(
    GLsizei p_width,
    GLsizei p_height,
    GLint p_format,
    GLenum p_type,
    const GLvoid* p_texels) {
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, p_format, p_width, p_height, 0, p_format, p_type, p_texels);

    return texId;
}
void utilGlUpdateTexture(
    GLuint p_texId,
    GLsizei p_width,
    GLsizei p_height,
    GLint p_format,
    GLenum p_type,
    const GLvoid* p_texels) {
    glBindTexture(GL_TEXTURE_2D, p_texId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, p_width, p_height, p_format, p_type, p_texels);
}