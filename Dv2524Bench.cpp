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

#include <cstring> // memset
#include <fstream> // ofstream
#include <unistd.h> // sleep
#include <stdlib.h> // system()
#include <fcntl.h>
#include <termios.h>

// Linux X11 Windowing system:
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "Timer.h"
#include "Dv2524Bench.h"

static Display* s_displayX11;

static EGLint s_attriblist[] = {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_RED_SIZE, 5,
    EGL_GREEN_SIZE, 6,
    EGL_BLUE_SIZE, 5,
    EGL_DEPTH_SIZE, 1,
    EGL_NONE
};

Dv2524Bench::Dv2524Bench(SCENE p_benchmark, int p_numFrames) {
    memset(&m_window, 0, sizeof(WindowEgl));

    m_benchmark = p_benchmark;
    m_numFrames = p_numFrames;
}
Dv2524Bench::~Dv2524Bench() {
}

int Dv2524Bench::init() {
    on_init(m_benchmark);

    const char* title = s_windowTitle;
    int width = s_windowWidth;
    int height = s_windowHeight;
    GLboolean isInited = createWindow(&m_window, title, width, height);

    if(isInited==true) {
        isInited = (GLboolean)on_surface_created();
        on_surface_changed(width, height);
    }
    return (int)isInited;
}
void Dv2524Bench::run() {
    // Won't stop if m_numFrames is less than zero to begin with. This is expected behaviour.
    Timer timer;
    int sercon = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    while(m_numFrames!=0) {
        // printf( "Frames left: %d...\n", m_numFrames );

        write(sercon, "dv2524_start\n", 13);
        tcdrain(sercon);

        //timer.start();

        on_draw_frame();

        //timer.stop();

        write(sercon, "dv2524_stop\n", 12);
        tcdrain(sercon);

        m_frametimes.push_back(timer.getElapsedTimeMilliSec());

        eglSwapBuffers(m_window.eglDisplay, m_window.eglSurface);
        timer.reset();

        m_numFrames--;
    }
    log();
    on_destroy();
}
void Dv2524Bench::log() {
    std::string filename = "../dv2524-bin/x11.ms";

    std::ofstream logfile(filename.c_str(), std::ofstream::out);
    if(logfile.is_open()==true) {
        for(unsigned i = 0; i<m_frametimes.size(); i++) {
            logfile << m_frametimes.at(i) << '\n';
        }

        logfile.close();
    }
}

GLboolean Dv2524Bench::createWindow(WindowEgl* p_window, const char* p_title, GLint p_width, GLint p_height) {
    EGLBoolean createdWindow = createWindowX11(p_window, p_title, p_width, p_height);
    if(createdWindow!=EGL_FALSE) {
        createdWindow = createWindowEgl(p_window->hWnd, &p_window->eglDisplay, &p_window->eglContext, &p_window->eglSurface, s_attriblist);
    }
    return (GLboolean)createdWindow;
}
EGLBoolean Dv2524Bench::createWindowX11(WindowEgl* o_window, const char* p_title, GLint p_width, GLint p_height) {
    // Initialize X11 display:
    s_displayX11 = XOpenDisplay(NULL);
    if(s_displayX11==NULL) {
        return EGL_FALSE;
    }
    Window root = DefaultRootWindow(s_displayX11);

    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;
    Window win = XCreateWindow(
                     s_displayX11, root,
                     0, 0,
                     p_width, p_height,
                     0,
                     CopyFromParent, InputOutput,
                     CopyFromParent,	CWEventMask,
                     &swa);

    XSetWindowAttributes xattr;
    xattr.override_redirect = false;
    XChangeWindowAttributes(s_displayX11, win, CWOverrideRedirect, &xattr);

    XWMHints hints;
    hints.input = true;
    hints.flags = InputHint;
    XSetWMHints(s_displayX11, win, &hints);

    // Make window visible:
    XMapWindow(s_displayX11, win);
    XStoreName(s_displayX11, win, p_title);

    // Get identifiers for provided atom name strings: <-- I don't know what this means.
    Atom wm_state = XInternAtom(s_displayX11, "_NET_WM_STATE", false);

    XEvent xev;
    std::memset(&xev, 0, sizeof(XEvent));
    xev.type 				= ClientMessage;
    xev.xclient.window 		= win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format 		= 32;
    xev.xclient.data.l[ 0 ] = 1;
    xev.xclient.data.l[ 1 ] = false;
    XSendEvent(
        s_displayX11,
        DefaultRootWindow(s_displayX11),
        false,
        SubstructureNotifyMask,
        &xev);

    o_window->hWnd = (EGLNativeWindowType)win;
    return EGL_TRUE;
}
EGLBoolean Dv2524Bench::createWindowEgl(EGLNativeWindowType p_hWnd, EGLDisplay* o_eglDisplay, EGLContext* o_eglContext, EGLSurface* o_eglSurface, EGLint p_attribList[]) {
    EGLDisplay display = eglGetDisplay((EGLNativeDisplayType)s_displayX11);
    if(display==EGL_NO_DISPLAY) {
        return EGL_FALSE;
    }

    EGLint majorVersion;
    EGLint minorVersion;
    EGLBoolean initializedEgl = eglInitialize(display, &majorVersion, &minorVersion);
    if(initializedEgl==EGL_FALSE) {
        return EGL_FALSE;
    }

    EGLint numConfigs;
    EGLBoolean retrievedEglConfigs = eglGetConfigs(display, NULL, 0, &numConfigs);
    if(retrievedEglConfigs==EGL_FALSE) {
        return EGL_FALSE;
    }

    EGLConfig config;
    EGLBoolean choseConfig = eglChooseConfig(display, p_attribList, &config, 1, &numConfigs);
    if(choseConfig==EGL_FALSE) {
        return EGL_FALSE;
    }

    EGLSurface surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)p_hWnd, NULL);
    if(surface==EGL_NO_SURFACE) {
        return EGL_FALSE;
    }

    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if(context==EGL_NO_CONTEXT) {
        return EGL_FALSE;
    }

    EGLBoolean contextIsCurrent = eglMakeCurrent(display, surface, surface, context);
    if(contextIsCurrent==EGL_FALSE) {
        return EGL_FALSE;
    }

    // Don't wait for refresh rate:
    EGLBoolean vsyncDisabled = eglSwapInterval(display, 0);
    if(vsyncDisabled==EGL_FALSE) {
        return EGL_FALSE;
    }

    *o_eglDisplay = display;
    *o_eglSurface = surface;
    *o_eglContext = context;
    return EGL_TRUE;
}
