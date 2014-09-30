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

#ifndef DV2524_BENCH_DV2524BENCH_H_
#define DV2524_BENCH_DV2524BENCH_H_

#include <vector>

#include "shared/shared.h"

struct WindowEgl {
    EGLNativeWindowType hWnd;
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLSurface eglSurface;
};

class Dv2524Bench {
  public:
    Dv2524Bench(SCENE p_benchmark, int p_numFrames);
    ~Dv2524Bench();

    int init();
    void run();
    void log();
  protected:
  private:
    GLboolean createWindow(WindowEgl* o_window, const char* p_title, GLint p_width, GLint p_height);
    EGLBoolean createWindowX11(WindowEgl* o_window, const char* p_title, GLint p_width, GLint p_height);
    EGLBoolean createWindowEgl(EGLNativeWindowType p_hWnd, EGLDisplay* o_eglDisplay, EGLContext* o_eglContext, EGLSurface* o_eglSurface, EGLint p_attribList[]);

    SCENE m_benchmark;
    int m_numFrames;
    std::vector<double> m_frametimes;
    WindowEgl m_window;
};

#endif /* DV2524_BENCH_DV2524BENCH_H_ */
