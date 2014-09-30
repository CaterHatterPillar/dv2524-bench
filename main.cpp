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

#include <string>
#include <stdio.h>

#include "Dv2524Bench.h"

SCENE strBenchmarkToSceneEnum(std::string p_str) {
    if(p_str=="julia") {
        return SCENE_Julia;
    } else if(p_str=="phong") {
        return SCENE_Phong;
    } else if(p_str=="chess") {
        return SCENE_Chess;
    }
    return SCENE_Invalid;
}

#define EXPECTED_NUM_CLI_ARGS 4+1
int main(int argc, const char* argv[]) {
    int retVal = -1;
    if(argc!=EXPECTED_NUM_CLI_ARGS) {
        printf("Usage: %s --benchmark BENCHMARK --numframes NUM_FRAMES", argv[ 0 ]);
    } else {
        std::string strBenchmark, strNumFrames;
        for(int i = 1; i<argc; i++) {
            if(std::string(argv[ i ])=="--benchmark") {
                strBenchmark = argv[ i + 1 ];
                i += 1;
            } else if(std::string(argv[ i ])=="--numframes") {
                strNumFrames = argv[ i + 1 ];
                i += 1;
            }
        }

        Dv2524Bench bench(strBenchmarkToSceneEnum(strBenchmark), atoi(strNumFrames.c_str()));
        retVal = bench.init();
        if(retVal!=0) {
            bench.run();
        } else {
            printf("main: Benchmark failed to initialize!\n");
        }
    }
    return retVal;
}
