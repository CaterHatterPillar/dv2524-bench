LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := bench
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../.. 
LOCAL_SRC_FILES := jni.c ../../shared/BenchGl.c ../../shared/utilgl.c ../../shared/util.c ../../shared/math.c ../../shared/timer.c ../../shared/sceneJulia.c ../../shared/scenePhong.c ../../shared/sceneChess.c
LOCAL_LDLIBS	:= -lGLESv2

include $(BUILD_SHARED_LIBRARY)
