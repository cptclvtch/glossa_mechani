#include <jni.h>

#include "../../../../../unit_testing.c"

#define INCLUDE_PRINTING
#include "../../../../../../../glossa_mechani.c"
#undef CLT

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_unit_1testing_MainActivity_stringFromJNI( JNIEnv* env, jobject /* this */)
{
    #include "../../../../../testing_body.c"
}