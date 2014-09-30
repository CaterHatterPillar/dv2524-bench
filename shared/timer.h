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

#ifndef DV2524_BENCH_TIMER_H
#define DV2524_BENCH_TIMER_H

void timerStart();
void timerStop();
void timerReset();
void timerTick();

double timerGetElapsedTimeMicroSec();
double timerGetElapsedTimeMilliSec();
double timerGetElapsedTimeSec();

double timerGetStartTimeMicroSec();
double timerGetStartTimeMilliSec();
double timerGetStartTimeSec();

double timerGetEndTimeMicroSec();
double timerGetEndTimeMilliSec();
double timerGetEndTimeSec();

#endif // DV2524_BENCH_TIMER_H
