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

#include <sys/time.h>

#include "timer.h"

static int s_ticking = 0;
static double s_startTimeMicroSec = 0;
static double s_endTimeMicroSec = 0;

static struct timeval s_startCount;
static struct timeval s_endCount;

void timerStart() {
    s_ticking = 1;

    s_startCount.tv_sec = 0;
    s_startCount.tv_usec = 0;
    s_endCount.tv_sec = 0;
    s_endCount.tv_usec = 0;

    gettimeofday(&s_startCount, 0);
    s_startTimeMicroSec = (s_startCount.tv_sec * 1000000.0) + s_startCount.tv_usec;
}
void timerStop() {
    s_ticking = 0;

    gettimeofday(&s_endCount, 0);
    s_endTimeMicroSec = (s_endCount.tv_sec * 1000000.0) + s_endCount.tv_usec;
}
void timerReset() {
    s_ticking = 0;
    s_startTimeMicroSec = 0;
    s_endTimeMicroSec = 0;

    s_startCount.tv_sec = 0;
    s_startCount.tv_usec = 0;
    s_endCount.tv_sec = 0;
    s_endCount.tv_usec = 0;
}
void timerTick() {
    if(s_ticking!=0) {
        gettimeofday(&s_endCount, 0);
        s_endTimeMicroSec = (s_endCount.tv_sec * 1000000.0) + s_endCount.tv_usec;
    }
}

double timerGetElapsedTimeMicroSec() {
    return s_endTimeMicroSec - s_startTimeMicroSec;
}
double timerGetElapsedTimeMilliSec() {
    return timerGetElapsedTimeMicroSec() * 0.001;
}
double timerGetElapsedTimeSec() {
    return timerGetElapsedTimeMicroSec() * 0.000001;
}

double timerGetStartTimeMicroSec() {
    return s_startTimeMicroSec;
}
double timerGetStartTimeMilliSec() {
    return timerGetStartTimeMicroSec() * 0.001;
}
double timerGetStartTimeSec() {
    return timerGetStartTimeMicroSec() * 0.000001;
}

double timerGetEndTimeMicroSec() {
    return s_endTimeMicroSec;
}
double timerGetEndTimeMilliSec() {
    return timerGetEndTimeMicroSec() * 0.001;
}
double timerGetEndTimeSec() {
    return timerGetEndTimeMicroSec() * 0.000001;
}
