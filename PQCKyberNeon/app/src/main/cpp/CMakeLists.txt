# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)


# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("pqckyberneon")
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
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon -mfloat-abi=softfp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon -mfloat-abi=softfp")

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

add_library(pqckyberneon SHARED native-lib.cpp
        aes256ctr.c
        cbd.c
        rng.c
        fips202.c
        fips202x2.c
        gen_ntt.c
        neon_ntt.c
        indcpa.c
        kem.c
        kex.c
        ntt.c
        poly.c
        polyvec.c
        neon_poly.c
        neon_polyvec.c
#        PQCgenKAT_kem.c
       # randombytes.c
        rejsample.c
        reduce.c
        sha256.c
        sha512.c
        symmetric-aes.c
        neon_symmetric-shake.c
#        test_kyber.c
       # test_speed.c
        test_speed_region.c
        #speed_print.c
        #speed_ntt.c
#        test_vectors.c
        #test_speed_usec.c
        symmetric-shake.c
#        test_kex.c
        verify.c
#        cpucycles.c
        )
# Link the OpenSSL libraries
add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/arm64-v8a/libcrypto.a)

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/arm64-v8a/libssl.a)

# Include directories
include_directories(include)
#include_directories(include/aarch64-linux-gnu)
#include_directories(include/bits/types)
find_library(log-lib log)

# Link the libraries to your target
target_link_libraries(
        pqckyberneon
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