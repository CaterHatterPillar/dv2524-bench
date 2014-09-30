/*
* The MIT License (MIT)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

/*
 * Parts of math.h and math.c are implemented in accordance to the OpenGL(R) ES 2.0 Programming Guide samples.
 * The samples are licensed under the MIT License (see http://code.google.com/p/opengles-book-samples/). The MIT License is attached above.
 *
 * Book:      OpenGL(R) ES 2.0 Programming Guide
 * Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
 * ISBN-10:   0321502795
 * ISBN-13:   9780321502797
 * Publisher: Addison-Wesley Professional
 * URLs:      http://safari.informit.com/9780321563835
 *				http://www.opengles-book.com
*/

#ifndef DV2524_BENCH_MATH_H
#define DV2524_BENCH_MATH_H

#define PI 3.1415926535897932384626433832795f

#include <math.h>

#include "glwrapper.h"

typedef struct Mat4f {
    GLfloat m[ 4 ][ 4 ];
} Mat4f;

typedef struct Vec4f {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} Vec4f;
Vec4f vec4fCreate(GLfloat p_r, GLfloat p_g, GLfloat p_b, GLfloat p_a);

void mat4fScale(Mat4f* io_result, GLfloat p_x, GLfloat p_y, GLfloat p_z);
void mat4fTranslate(Mat4f *io_result, GLfloat p_x, GLfloat p_y, GLfloat p_z);
void mat4fRotate(Mat4f* io_result, GLfloat p_angle, GLfloat p_x, GLfloat p_y, GLfloat p_z);
void mat4fFrustum(Mat4f* io_result, float p_left, float p_right, float p_bottom, float p_top, float p_zNear, float p_zFar);
void mat4fPerspective(Mat4f* io_result, float p_fovy, float p_aspect, float p_zNear, float p_zFar);
void mat4fMatrixMultiply(Mat4f* io_result, Mat4f* p_a, Mat4f* p_b);
void mat4fMatrixLoadIdentity(Mat4f* io_result);

#endif // DV2524_BENCH_MATH_H
