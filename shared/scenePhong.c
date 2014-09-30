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
#include "obj/teapot.h"
#include "tex/albedo1448.h"

#define VERTEX_POS_SIZE 3
#define VERTEX_NOR_SIZE 3
#define VERTEX_TEX_SIZE 2

#define VERTEX_POS_IDX 0
#define VERTEX_NOR_IDX 1
#define VERTEX_TEX_IDX 2

#define VERTEX_POS_LEN 3*sizeof(float)
#define VERTEX_NOR_LEN 3*sizeof(float)
#define VERTEX_TEX_LEN 2*sizeof(float)

typedef struct ScenePhong {
    GLuint idProgram;
    GLuint idShaderVert;
    GLuint idShaderFrag;
    GLuint idTexAlbedo;

    GLint locAttributePos;
    GLint locAttributeNor;
    GLint locAttributeTex;
    GLint locUniformMvp;
    GLint locUniformVp;

    char* texelsAlbedo;

    Mat4f mvp;
    Mat4f vp;
    GLfloat rotAngle;
    GLfloat aspectRatio;
} ScenePhong;

static const char* s_shaderPhongVert =
    "uniform mat4 u_vp;													\n"
    "uniform mat4 u_mvp;												\n"
    "attribute vec4 a_pos;												\n"
    "attribute vec3 a_nor;												\n"
    "attribute vec2 a_tex;												\n"
    "varying vec3 v_pos;												\n"
    "varying vec3 v_nor;												\n"
    "varying vec2 v_tex;												\n"
    "void main() {														\n"
    "	v_pos = ( u_vp * vec4( a_pos.xyz, 1.0 ) ).xyz;					\n"
    "	v_nor = ( u_mvp * vec4( normalize( a_nor ), 0.0 ) ).xyz;		\n"
    "	v_tex = a_tex;													\n"
    "	gl_Position = u_mvp * vec4( a_pos.xyz, 1.0 );					\n"
    "}																	\n";

static const char* s_shaderPhongFrag =
    "precision mediump float;											\n"
    "uniform sampler2D u_tex;											\n"
    "varying vec3 v_pos;												\n"
    "varying vec3 v_nor;												\n"
    "varying vec2 v_tex;												\n"
    "const vec3 c_lPos = vec3( -1.0, 1.0, 0.0 );						\n"
    "const vec3 c_lAmbi = vec3( 0.3, 0.3, 0.3 );						\n"
    "const vec3 c_lDiff = vec3( 0.5, 0.5, 0.5 );						\n"
    "const vec3 c_lSpec = vec3( 1.0, 1.0, 1.0 );						\n"
    "void main() {														\n"
    "	vec3 nor = normalize( v_nor );									\n"
    "	vec3 lDir = normalize( c_lPos - v_pos );						\n"
    "	vec3 lDirReflect = reflect( -lDir, nor );						\n"
    "	vec3 viewDir = normalize( -v_pos );								\n"
    "	float lambert = max( dot( lDir, nor ), 0.0 );					\n"
    "	float spec = 0.0;												\n"
    "	if( lambert>0.0 ) {												\n"
    "		float specAngle = max( dot( lDirReflect, viewDir ), 0.0 );	\n"
    "		spec = pow( specAngle, 4.0 );								\n"
    "	}																\n"
    "	gl_FragColor = vec4(											\n"
    "		texture2D( u_tex, v_tex ).xyz								\n"
    "		+ c_lDiff * lambert											\n"
    "		+ c_lSpec * spec, 1.0 );	 								\n"
    "}																	\n";

int scenePhongOnCreated(Scene* io_scene) {
    memset(io_scene, 0, sizeof(Scene));
    io_scene->data = malloc(sizeof(ScenePhong));
    ScenePhong* scenePhong = (ScenePhong*)io_scene->data;
    memset(scenePhong, 0, sizeof(ScenePhong));

    GLuint success = GL_TRUE;
    scenePhong->idProgram = glCreateProgram();
    if(scenePhong->idProgram==0) {
        printf("scenePhongOnCreated: program creation failed!\n");
        success = GL_FALSE;
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(
                      &scenePhong->idShaderVert,
                      GL_VERTEX_SHADER,
                      s_shaderPhongVert);
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(
                      &scenePhong->idShaderFrag,
                      GL_FRAGMENT_SHADER,
                      s_shaderPhongFrag);
    }
    if(success==GL_TRUE) {
        glAttachShader(scenePhong->idProgram, scenePhong->idShaderVert);
        glAttachShader(scenePhong->idProgram, scenePhong->idShaderFrag);
        glLinkProgram(scenePhong->idProgram);

        scenePhong->locUniformVp = glGetUniformLocation(scenePhong->idProgram, "u_vp");
        scenePhong->locUniformMvp = glGetUniformLocation(scenePhong->idProgram, "u_mvp");
        scenePhong->locAttributePos = glGetAttribLocation(scenePhong->idProgram, "a_pos");
        scenePhong->locAttributeNor = glGetAttribLocation(scenePhong->idProgram, "a_nor");
        scenePhong->locAttributeTex = glGetAttribLocation(scenePhong->idProgram, "a_tex");

        // Load RGBA texture from raw data:
        char* data = albedoData;

        int numTexels = albedoWidth * albedoHeight;
        scenePhong->texelsAlbedo = (char*)malloc(numTexels * 4);
        char* texel = scenePhong->texelsAlbedo;
        GLubyte* texture = (GLubyte*)texel;
        while(numTexels-->0) {
            texel[0] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33)));
            texel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2));
            texel[2] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4));
            texel[3] = 0;
            data += 4;
            texel += 4;
        }
        scenePhong->idTexAlbedo = utilGlCreateTexture(albedoWidth, albedoHeight, GL_RGBA, GL_UNSIGNED_BYTE, texture);

        scenePhong->rotAngle = 45.0f;
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    }

    return success;
}
void scenePhongOnChanged(Scene* io_scene, int p_width, int p_height) {
    ScenePhong* scenePhong = (ScenePhong*)io_scene->data;

    io_scene->winWidth = p_width;
    io_scene->winHeight = p_height;
    scenePhong->aspectRatio = (GLfloat)io_scene->winWidth / (GLfloat)io_scene->winHeight;
}
void scenePhongOnDraw(Scene* io_scene) {
    ScenePhong* scenePhong = (ScenePhong*)io_scene->data;

    scenePhong->rotAngle += (0.1 * 40.0f);
    if(scenePhong->rotAngle >= 360.0f) {
        scenePhong->rotAngle -= 360.0f;
    }

    Mat4f v, p, vp, mvp;
    mat4fMatrixLoadIdentity(&p);
    mat4fPerspective(&p, 60.0f, scenePhong->aspectRatio, 1.0f, 20.0f);
    mat4fMatrixLoadIdentity(&v);
    mat4fTranslate(&v, 0.0, 0.0, -2.0);
    mat4fRotate(&v, scenePhong->rotAngle, 1.0, 0.0, 1.0);
    mat4fMatrixMultiply(&vp, &v, &p);
    mat4fMatrixMultiply(&mvp, &v, &p);
    scenePhong->vp = vp;
    scenePhong->mvp = mvp;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, io_scene->winWidth, io_scene->winHeight);
    glUseProgram(scenePhong->idProgram);

    glEnableVertexAttribArray(VERTEX_POS_IDX);
    glEnableVertexAttribArray(VERTEX_NOR_IDX);
    glEnableVertexAttribArray(VERTEX_TEX_IDX);

    // Update texture data every frame:
    utilGlUpdateTexture(scenePhong->idTexAlbedo, albedoWidth, albedoHeight, GL_RGBA, GL_UNSIGNED_BYTE, scenePhong->texelsAlbedo);

    // Update vertex data every frame:
    glVertexAttribPointer(VERTEX_POS_IDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_POS_LEN, teapotVertices);
    glVertexAttribPointer(VERTEX_NOR_IDX, VERTEX_NOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_NOR_LEN, teapotNormals);
    glVertexAttribPointer(VERTEX_TEX_IDX, VERTEX_TEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_TEX_LEN, teapotTextureCoordinates);
    glUniformMatrix4fv(scenePhong->locUniformVp, 1, GL_FALSE, (GLfloat*)&scenePhong->vp.m[0][0]);
    glUniformMatrix4fv(scenePhong->locUniformMvp, 1, GL_FALSE, (GLfloat*)&scenePhong->mvp.m[0][0]);

    glEnable(GL_DEPTH_TEST);
    //glEnable( GL_CULL_FACE );
    glDrawArrays(GL_TRIANGLES, 0, teapotNumVertices);
    glFinish();
}
void scenePhongOnDestroy(Scene* io_scene) {
    ScenePhong* scenePhong = (ScenePhong*)io_scene->data;
    free(scenePhong->texelsAlbedo);

    free(io_scene->data);
}
