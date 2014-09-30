#include <jni.h>
#include "../../shared/BenchGl.h"

JNIEXPORT void JNICALL Java_com_example_dv2524_1bench_1android_BenchLibJniWrapper_on_1init(JNIEnv* env, jclass cls, jint scene) {
    on_init(scene);
}

JNIEXPORT int JNICALL Java_com_example_dv2524_1bench_1android_BenchLibJniWrapper_on_1surface_1created(JNIEnv* env, jclass cls) {
    return on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_dv2524_1bench_1android_BenchLibJniWrapper_on_1surface_1changed(JNIEnv* env, jclass cls, jint width, jint height) {
    on_surface_changed(width, height);
}

JNIEXPORT void JNICALL Java_com_example_dv2524_1bench_1android_BenchLibJniWrapper_on_1draw_1frame(JNIEnv* env, jclass cls) {
    on_draw_frame();
}

JNIEXPORT void JNICALL Java_com_example_dv2524_1bench_1android_BenchLibJniWrapper_on_1destroy(JNIEnv* env, jclass cls) {
    on_destroy();
}
