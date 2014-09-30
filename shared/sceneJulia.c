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
#include "tex/palette.h"

typedef struct SceneJulia {
    GLuint idProgram;
    GLuint idShaderVert;
    GLuint idShaderFrag;
    GLuint idTexPalette;

    GLfloat seedX;
    GLfloat seedY;
    GLint numIt;

    GLfloat fsqVertices[ 16 ]; // full screen quad
    GLushort fsqIndices[ 6 ];
} SceneJulia;

static const char* s_shaderJuliaVert =
    "attribute vec4 a_pos;                		\n"
    "attribute vec2 a_tex;						\n"
    "varying vec2 v_tex;						\n"
    "void main() {                            	\n"
    "	v_tex = a_tex;							\n"
    "   gl_Position = a_pos;	  				\n"
    "}                                         	\n";

static const char* s_shaderJuliaFrag =
    "precision mediump float;                           						\n"
    "uniform sampler2D u_tex;													\n"
    "uniform vec2 u_c;															\n"
    "uniform int u_numIt;														\n"
    "varying vec2 v_tex;														\n"
    "void main() {																\n"
    "	vec2 z;																	\n"
    "	z.x = 3.0 * ( v_tex.x - 0.5	);											\n"
    "	z.y = 2.0 * ( v_tex.y - 0.5	);											\n"
    "																			\n"
    "	int i, j = 0;															\n"
    "	for( i = 0; i<u_numIt; i++ ) {											\n"
    "		float x = ( z.x * z.x - z.y * z.y ) + u_c.x;						\n"
    "		float y = ( z.y * z.x + z.x * z.y ) + u_c.y;						\n"
    "																			\n"
    "		if( ( x*x + y*y )<4.0 ) {											\n"
    "			z.x = x;														\n"
    "			z.y = y;														\n"
    "			j = i;															\n"
    "		}																	\n"
    "	}																		\n"
    "																			\n"
    "	float texX = 0.0;														\n"
    "	if( j!=u_numIt ) {														\n"
    "		texX = float( j ) / 100.0;											\n"
    "	}																		\n"
    "	gl_FragColor = texture2D( u_tex, vec2( texX, 0.0 ) );					\n"
    "}																			\n";

int sceneJuliaOnCreated(Scene* io_scene) {
    memset(io_scene, 0, sizeof(Scene));
    io_scene->data = malloc(sizeof(SceneJulia));
    SceneJulia* sceneJulia = (SceneJulia*)io_scene->data;
    memset(sceneJulia, 0, sizeof(SceneJulia));

    GLuint success = GL_TRUE;
    sceneJulia->idProgram = glCreateProgram();
    if(sceneJulia->idProgram==0) {
        printf("sceneJuliaOnCreated: program creation failed!\n");
        success = GL_FALSE;
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(
                      &sceneJulia->idShaderVert,
                      GL_VERTEX_SHADER,
                      s_shaderJuliaVert);
    }
    if(success==GL_TRUE) {
        success = utilGlCreateShader(
                      &sceneJulia->idShaderFrag,
                      GL_FRAGMENT_SHADER,
                      s_shaderJuliaFrag);
    }
    if(success==GL_TRUE) {
        glAttachShader(sceneJulia->idProgram, sceneJulia->idShaderVert);
        glAttachShader(sceneJulia->idProgram, sceneJulia->idShaderFrag);
        glLinkProgram(sceneJulia->idProgram);

        char* data = paletteData;
        int numTexels = paletteWidth * paletteHeight;
        char* texel = (char*)malloc(numTexels * 4);   // RGBA
        GLubyte* texture = (GLubyte*)texel;
        while(numTexels-->0) {
            texel[0] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33)));
            texel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2));
            texel[2] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4));
            texel[3] = 0;
            data += 4;
            texel += 4;
        }
        sceneJulia->idTexPalette = utilGlCreateTexture(paletteWidth, paletteHeight, GL_RGBA, GL_UNSIGNED_BYTE, texture);
        free(texture);   // glTexImage2D copies data. We may release texture.

        // Original = 450
        // Halved = 225
        // Doubled = 900
        sceneJulia->numIt = 450;
        GLfloat vertices[ 16 ] = {
            -1.0, -1.0,
            0.0, 0.0,

            1.0, -1.0,
            1.0, 0.0,

            1.0, 1.0,
            1.0, 1.0,

            -1.0, 1.0,
            0.0, 1.0
        };
        memcpy(sceneJulia->fsqVertices, vertices, 16 * sizeof(GLfloat));
        GLushort indices[ 6 ] = {
            0, 1, 2,
            0, 2, 3
        };
        memcpy(sceneJulia->fsqIndices, indices, 6 * sizeof(GLushort));

        timerStart();
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    }
    return success;
}
void sceneJuliaOnChanged(Scene* io_scene, int p_width, int p_height) {
    io_scene->winWidth = p_width;
    io_scene->winHeight = p_height;
}
void sceneJuliaOnDraw(Scene* io_scene) {
    SceneJulia* sceneJulia = (SceneJulia*)io_scene->data;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, io_scene->winWidth, io_scene->winHeight);
    glUseProgram(sceneJulia->idProgram);

    timerTick();
    float t = (float)timerGetElapsedTimeSec();
    sceneJulia->seedX = (sin(cos(t / 10) * 10) + cos(t * 2.0) / 4.0 + sin(t * 3.0) / 6.0) * 0.8;
    sceneJulia->seedY = (cos(sin(t / 10) * 10) + sin(t * 2.0) / 4.0 + cos(t * 3.0) / 6.0) * 0.8;

    int loc = glGetUniformLocation(sceneJulia->idProgram, "u_c");
    glUniform2f(loc, sceneJulia->seedX, sceneJulia->seedY);

    loc = glGetUniformLocation(sceneJulia->idProgram, "u_numIt");
    glUniform1i(loc, sceneJulia->numIt);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &sceneJulia->fsqVertices[ 0 ]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &sceneJulia->fsqVertices[ 2 ]);
    glBindAttribLocation(sceneJulia->idProgram, 0, "a_pos");
    glBindAttribLocation(sceneJulia->idProgram, 1, "a_tex");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &sceneJulia->fsqIndices[ 0 ]);
    glFinish();
}
void sceneJuliaOnDestroy(Scene* io_scene) {
    free(io_scene->data);
}

/*
* Fractal computation implemented in accordance to John Tsiombikas Julia-fractal in OpenGL (public domain)
* See http://nuclear.mutantstargoat.com/articles/sdr_fract/
*/

//static const char* s_shaderJuliaFrag =
//	"precision mediump float;                           						\n"
//	"uniform sampler2D u_tex;													\n"
//	"uniform vec2 u_c;															\n"
//	"uniform int u_numIt;														\n"
//	"varying vec2 v_tex;														\n"
//	"void main() {																\n"
//	"	vec2 z;																	\n"
//	"	z.x = 3.0 * ( v_tex.x - 0.5	);											\n"
//	"	z.y = 2.0 * ( v_tex.y - 0.5	);											\n"
//    "																			\n"
//	"	int i;																	\n"
//	"	for( i = 0; i<u_numIt; i++ ) {											\n"
//	"		float x = ( z.x * z.x - z.y * z.y ) + u_c.x;						\n"
//	"		float y = ( z.y * z.x + z.x * z.y ) + u_c.y;						\n"
//    "																			\n"
//	"		if( ( x*x + y*y )>4.0 ) {											\n"
//	"			break;															\n"
//	"		}																	\n"
//	"		z.x = x;															\n"
//	"		z.y = y;															\n"
//	"	}																		\n"
//    "																			\n"
//	"	float texX = 0.0;														\n"
//	"	if( i!=u_numIt ) {														\n"
//	"		texX = float( i ) / 100.0;											\n"
//	"	}																		\n"
//	"	gl_FragColor = texture2D( u_tex, vec2( texX, 0.0 ) );					\n"
//	"}																			\n";