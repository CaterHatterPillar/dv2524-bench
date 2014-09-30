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

#include "scene.h"

#include <unistd.h> //temp

// Original: 84
// Doubled: 118
// Halved: 60
#define NUM_CHESS_TILES_X 84
#define NUM_CHESS_TILES_Y 84

typedef struct ChessTile {
    GLuint vbo;
    GLuint ibo;

    Vec4f color;
    unsigned numIndices;
} ChessTile;

typedef struct SceneChess {
    GLuint idProgram;
    GLuint idShaderVert;
    GLuint idShaderFrag;

    GLuint locAttributePos;
    GLuint locUniformCol;

    ChessTile tiles[ NUM_CHESS_TILES_X*NUM_CHESS_TILES_Y ];
} SceneChess;

static const char* s_shaderChessVert =
    "attribute vec4 a_pos;		\n"
    "void main() {				\n"
    "	gl_Position = a_pos;	\n"
    "}							\n";

static const char* s_shaderChessFrag =
    "precision mediump float;	\n"
    "uniform vec4 u_col;		\n"
    "void main() {				\n"
    "	gl_FragColor = u_col;	\n"
    "}							\n";

int sceneChessOnCreated(Scene* io_scene) {
    memset(io_scene, 0, sizeof(Scene));
    io_scene->data = malloc(sizeof(SceneChess));
    SceneChess* sceneChess = (SceneChess*)io_scene->data;
    memset(sceneChess, 0, sizeof(SceneChess));

    GLuint success = GL_TRUE;
    sceneChess->idProgram = glCreateProgram();
    if(sceneChess->idProgram==0) {
        printf("sceneChessOnCreated: program creation failed!\n");
        success = GL_FALSE;
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(&sceneChess->idShaderVert, GL_VERTEX_SHADER, s_shaderChessVert);
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(&sceneChess->idShaderFrag, GL_FRAGMENT_SHADER, s_shaderChessFrag);
    }
    if(success==GL_TRUE) {
        glAttachShader(sceneChess->idProgram, sceneChess->idShaderVert);
        glAttachShader(sceneChess->idProgram, sceneChess->idShaderFrag);
        glLinkProgram(sceneChess->idProgram);

        sceneChess->locAttributePos = glGetAttribLocation(sceneChess->idProgram, "a_pos");
        sceneChess->locUniformCol = glGetUniformLocation(sceneChess->idProgram, "u_col");

        int x, y;
        float offsetX = -1.0;
        float offsetY = 1.0;
        float tileWidth = 2.0 / NUM_CHESS_TILES_X;
        bool isBlack = false;
        for(x = 0; x<NUM_CHESS_TILES_X; x++) {
            for(y = 0; y<NUM_CHESS_TILES_Y; y++) {
                GLfloat vertices[ 8 ] = {
                    offsetX, offsetY,
                    offsetX + tileWidth, offsetY,
                    offsetX, offsetY - tileWidth,
                    offsetX + tileWidth, offsetY - tileWidth
                };
                GLushort indices[] = {
                    0, 1, 2,
                    1, 2, 3
                };

                ChessTile* obj = &sceneChess->tiles[ x*NUM_CHESS_TILES_X+y ];
                glGenBuffers(2, &obj->vbo);
                glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
                glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indices, GL_STATIC_DRAW);
                obj->numIndices = 6;
                if(isBlack==true) {
                    obj->color = vec4fCreate(0.0, 0.0, 0.0, 1.0);
                } else {
                    obj->color = vec4fCreate(1.0, 1.0, 1.0, 1.0);
                }
                isBlack = !isBlack;
                offsetY -= tileWidth;
            }
            isBlack = !isBlack; // flip for next column
            offsetX += tileWidth;
            offsetY = 1.0;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    return success;
}
void sceneChessOnChanged(Scene* io_scene, int p_width, int p_height) {
    io_scene->winWidth = p_width;
    io_scene->winHeight = p_height; // These aren't used. Consider removing.
}
void sceneChessOnDraw(Scene* io_scene) {
    SceneChess* sceneChess = (SceneChess*)io_scene->data;

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(sceneChess->idProgram);

    int i;
    for(i = 0; i<NUM_CHESS_TILES_X*NUM_CHESS_TILES_Y; i++) {
        ChessTile* tile = &sceneChess->tiles[ i ];

        glBindBuffer(GL_ARRAY_BUFFER, tile->vbo);
        glEnableVertexAttribArray(sceneChess->locAttributePos);
        glVertexAttribPointer(sceneChess->locAttributePos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tile->ibo);

        glUniform4f(sceneChess->locUniformCol, tile->color.r, tile->color.g, tile->color.b, tile->color.a);

        glDrawElements(GL_TRIANGLES, tile->numIndices, GL_UNSIGNED_SHORT, 0);
    }
    glFinish();
}
void sceneChessOnDestroy(Scene* io_scene) {
    SceneChess* sceneChess = (SceneChess*)io_scene->data;

    int i;
    for(i = 0; i<NUM_CHESS_TILES_X*NUM_CHESS_TILES_Y; i++) {
        ChessTile* tile = &sceneChess->tiles[ i ];
        glDeleteBuffers(2, &tile->vbo);
    }

    free(sceneChess);
}