#include <jni.h>
#include <string>
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/crypto.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_applicationnew_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}