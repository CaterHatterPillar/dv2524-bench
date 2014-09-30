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

#ifndef DV2520_TIMER_H
#define DV2520_TIMER_H

// High precision time measurements are system specific:
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif // _WIN32

class Timer {
  private:
    bool m_ticking;
    double m_startTimeMicroSec;
    double m_endTimeMicroSec;

#ifdef _WIN32
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_startCount;
    LARGE_INTEGER m_endCount;
#else
    timeval m_startCount;
    timeval m_endCount;
#endif // _WIN32
  protected:
  public:
    Timer();
    virtual ~Timer();

    void start();
    void stop();
    void reset();

    double getElapsedTimeMicroSec();
    double getElapsedTimeMilliSec();
    double getElapsedTimeSec();

    double getStartTimeMicroSec() const;
    double getStartTimeMilliSec() const;
    double getStartTimeSec() const;

    double getEndTimeMicroSec() const;
    double getEndTimeMilliSec() const;
    double getEndTimeSec() const;
};

#endif // DV2520_TIMER_H