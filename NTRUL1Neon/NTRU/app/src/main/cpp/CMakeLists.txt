# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)


# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("ntru")
# Set the path to your OpenSSL library and headers
#set(OPENSSL_ROOT_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)
#set(OPENSSL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/include)
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# Specify ABI
# Define the path to your NDK
set(ANDROID_NDK /home/qr/Android/Sdk/ndk/20.0.5594570)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffast-math -march=armv7-a -mfpu=neon")
# Add standard include paths
include_directories(${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include)
#include_directories(${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/c++/v1)

set(CMAKE_ANDROID_ARCH_ABI  "arm64-v8a")
# Enable NEON for arm64-v8a
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a+simd")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a+simd")
endif()

add_library(ntru SHARED native-lib.cpp
        cmov.c
        crypto_sort_int32.c
        fips202.c
        kem.c
        owcpa.c
        neon_batch_multiplication.c
        neon_matrix_transpose.c
        neon_poly_lift.c
        neon_poly_mod.c
        neon_poly_rq_mul.c
        neon_sample_iid.c
        pack3.c
        packq.c
        poly.c
        poly_r2_inv.c
        poly_s3_inv.c
        randombytes.c
        rng.c
        sample.c
        test/speed.c
        )
# Link the OpenSSL libraries
add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/arm64-v8a/libcrypto.a)

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/arm64-v8a/libssl.a)

# Include directories
include_directories(include)
include_directories(test)
#include_directories(include/aarch64-linux-gnu)
#include_directories(include/bits/types)
find_library(log-lib log)

# Link the libraries to your target
target_link_libraries(
        ntru
        ssl
        crypto
        log
        android
)
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
#target_link_libraries(${CMAKE_PROJECT_NAME}
#        # List libraries link to the target library
     #   android
      #  log)