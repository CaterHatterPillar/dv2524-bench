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
 * http://www.opengles-book.com
*/

#include "math.h"
#include "common.h"

Vec4f vec4fCreate(GLfloat p_r, GLfloat p_g, GLfloat p_b, GLfloat p_a) {
    Vec4f vec;
    vec.r = p_r;
    vec.g = p_g;
    vec.b = p_b;
    vec.a = p_a;
    return vec;
}

void mat4fScale(Mat4f* io_result, GLfloat p_x, GLfloat p_y, GLfloat p_z) {
    io_result->m[0][0] *= p_x;
    io_result->m[0][1] *= p_x;
    io_result->m[0][2] *= p_x;
    io_result->m[0][3] *= p_x;

    io_result->m[1][0] *= p_y;
    io_result->m[1][1] *= p_y;
    io_result->m[1][2] *= p_y;
    io_result->m[1][3] *= p_y;

    io_result->m[2][0] *= p_z;
    io_result->m[2][1] *= p_z;
    io_result->m[2][2] *= p_z;
    io_result->m[2][3] *= p_z;
}
void mat4fTranslate(Mat4f *io_result, GLfloat p_x, GLfloat p_y, GLfloat p_z) {
    io_result->m[3][0] += (io_result->m[0][0] * p_x + io_result->m[1][0] * p_y + io_result->m[2][0] * p_z);
    io_result->m[3][1] += (io_result->m[0][1] * p_x + io_result->m[1][1] * p_y + io_result->m[2][1] * p_z);
    io_result->m[3][2] += (io_result->m[0][2] * p_x + io_result->m[1][2] * p_y + io_result->m[2][2] * p_z);
    io_result->m[3][3] += (io_result->m[0][3] * p_x + io_result->m[1][3] * p_y + io_result->m[2][3] * p_z);
}
void mat4fRotate(Mat4f* io_result, GLfloat p_angle, GLfloat p_x, GLfloat p_y, GLfloat p_z) {
    GLfloat sinAngle, cosAngle;
    GLfloat mag = sqrtf(p_x * p_x + p_y * p_y + p_z * p_z);

    sinAngle = sinf(p_angle * PI / 180.0f);
    cosAngle = cosf(p_angle * PI / 180.0f);
    if(mag>0.0f) {
        GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
        GLfloat oneMinusCos;
        Mat4f rotMat;

        p_x /= mag;
        p_y /= mag;
        p_z /= mag;

        xx = p_x * p_x;
        yy = p_y * p_y;
        zz = p_z * p_z;
        xy = p_x * p_y;
        yz = p_y * p_z;
        zx = p_z * p_x;
        xs = p_x * sinAngle;
        ys = p_y * sinAngle;
        zs = p_z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
        rotMat.m[0][1] = (oneMinusCos * xy) - zs;
        rotMat.m[0][2] = (oneMinusCos * zx) + ys;
        rotMat.m[0][3] = 0.0F;

        rotMat.m[1][0] = (oneMinusCos * xy) + zs;
        rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
        rotMat.m[1][2] = (oneMinusCos * yz) - xs;
        rotMat.m[1][3] = 0.0F;

        rotMat.m[2][0] = (oneMinusCos * zx) - ys;
        rotMat.m[2][1] = (oneMinusCos * yz) + xs;
        rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
        rotMat.m[2][3] = 0.0F;

        rotMat.m[3][0] = 0.0F;
        rotMat.m[3][1] = 0.0F;
        rotMat.m[3][2] = 0.0F;
        rotMat.m[3][3] = 1.0F;

        mat4fMatrixMultiply(io_result, &rotMat, io_result);
    }
}
void mat4fFrustum(Mat4f* io_result, float p_left, float p_right, float p_bottom, float p_top, float p_zNear, float p_zFar) {
    float deltaX = p_right - p_left;
    float deltaY = p_top - p_bottom;
    float deltaZ = p_zFar - p_zNear;
    Mat4f frust;

    if((p_zNear <= 0.0f) || (p_zFar <= 0.0f) || (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f)) {
        return;
    }

    frust.m[0][0] = 2.0f * p_zNear / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * p_zNear / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (p_right + p_left) / deltaX;
    frust.m[2][1] = (p_top + p_bottom) / deltaY;
    frust.m[2][2] = -(p_zNear + p_zFar) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * p_zNear * p_zFar / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    mat4fMatrixMultiply(io_result, &frust, io_result);
}
void mat4fPerspective(Mat4f* io_result, float p_fovy, float p_aspect, float p_zNear, float p_zFar) {
    GLfloat frustumW, frustumH;

    frustumH = tanf(p_fovy / 360.0f * PI) * p_zNear;
    frustumW = frustumH * p_aspect;

    mat4fFrustum(io_result, -frustumW, frustumW, -frustumH, frustumH, p_zNear, p_zFar);
}
void mat4fMatrixMultiply(Mat4f* io_result, Mat4f* p_a, Mat4f* p_b) {
    Mat4f tmp;

    int i;
    for(i=0; i<4; i++) {
        tmp.m[i][0] = (p_a->m[i][0] * p_b->m[0][0]) +
                      (p_a->m[i][1] * p_b->m[1][0]) +
                      (p_a->m[i][2] * p_b->m[2][0]) +
                      (p_a->m[i][3] * p_b->m[3][0]);

        tmp.m[i][1] = (p_a->m[i][0] * p_b->m[0][1]) +
                      (p_a->m[i][1] * p_b->m[1][1]) +
                      (p_a->m[i][2] * p_b->m[2][1]) +
                      (p_a->m[i][3] * p_b->m[3][1]);

        tmp.m[i][2] = (p_a->m[i][0] * p_b->m[0][2]) +
                      (p_a->m[i][1] * p_b->m[1][2]) +
                      (p_a->m[i][2] * p_b->m[2][2]) +
                      (p_a->m[i][3] * p_b->m[3][2]) ;

        tmp.m[i][3] = (p_a->m[i][0] * p_b->m[0][3]) +
                      (p_a->m[i][1] * p_b->m[1][3]) +
                      (p_a->m[i][2] * p_b->m[2][3]) +
                      (p_a->m[i][3] * p_b->m[3][3]);
    }
    memcpy(io_result, &tmp, sizeof(Mat4f));
}
void mat4fMatrixLoadIdentity(Mat4f* io_result) {
    memset(io_result, 0x0, sizeof(Mat4f));
    io_result->m[0][0] = 1.0f;
    io_result->m[1][1] = 1.0f;
    io_result->m[2][2] = 1.0f;
    io_result->m[3][3] = 1.0f;
}
