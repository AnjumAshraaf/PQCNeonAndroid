#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "kex.h"
#include "kem.h"
#include "params.h"
#include "indcpa.h"
#include "poly.h"
#include "polyvec.h"
#include "neon_ntt.h"
#include <jni.h>
#include <string.h>
#include <android/log.h>
#include <sys/auxv.h>

#define NEON_FLAG (1 << 12)
//#define TIME(s) s = cpucycles();
// Result is nanosecond per call
//#define  CALC(start, stop) (stop - start)/NTESTS;

#define NTESTS 1000
#define LOG_TAG "TestKyber512Neon"

#define TIME(s,name) clock_gettime(CLOCK_MONOTONIC_RAW, &s);
// Result is nanosecond per call
#define  CALC(start, stop) \
  ((double) ((stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec - start.tv_nsec))) / NTESTS;

static
void VectorVectorMul(poly *mp, polyvec *b, polyvec *skpv)
{
  neon_polyvec_ntt(b);
  neon_polyvec_acc_montgomery(mp, skpv, b, 0);
  neon_invntt(mp->coeffs);
}

static
void MatrixVectorMul(polyvec at[KYBER_K], polyvec *sp, polyvec *b)
{
  neon_polyvec_ntt(sp);
  // matrix-vector multiplication
  for(int i=0;i<KYBER_K;i++)
    neon_polyvec_acc_montgomery(&b->vec[i], &at[i], sp, 0);

  neon_polyvec_invntt_to_mont(b);
}

uint8_t seed[KYBER_SYMBYTES] = {0};

JNIEXPORT jint JNICALL
        Java_com_example_pqckyberneon_MainActivity_runCCode(JNIEnv *env, jobject obj)
{
  unsigned int i;
  unsigned char pk[CRYPTO_PUBLICKEYBYTES] = {0};
  unsigned char sk[CRYPTO_SECRETKEYBYTES] = {0};
  unsigned char ct[CRYPTO_CIPHERTEXTBYTES] = {0};
  unsigned char key[CRYPTO_BYTES] = {0};
  unsigned char kexsenda[KEX_AKE_SENDABYTES] = {0};
  unsigned char kexsendb[KEX_AKE_SENDBBYTES] = {0};
  unsigned char kexkey[KEX_SSBYTES] = {0};
  unsigned char msg[KYBER_INDCPA_MSGBYTES] = {0};
  polyvec matrix[KYBER_K];
  poly ap, bp;
  polyvec sp, b;

  struct timespec start, stop;
  long ns;

    unsigned long hwcaps = getauxval(AT_HWCAP);
    if (hwcaps & NEON_FLAG) {
        //printf("✅ NEON is enabled on this device!\n");
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, " NEON is enabled on this device!");
    } else {
        //printf("❌ NEON is NOT enabled on this device.\n");
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, " NEON is enabled on this device!");
    }

  TIME(start, "gstime");
  for(i=0;i<NTESTS;i++) {
    gen_matrix(matrix, seed, 0);
  }
  TIME(stop, "getime");
  ns = CALC(start, stop);
  printf("gen_matrix: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of Gen Matrix is: %d", ns);

  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    neon_poly_getnoise_eta1_2x(&ap, &bp, seed, 0, 1);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("neon_poly_getnoise_eta1_2x: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of neon_poly_getnoise_eta1_2x is: %d", ns);
  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    neon_poly_getnoise_eta2(&ap, seed, 0);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("neon_poly_getnoise_eta2: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of neon_poly_getnoise_eta2 is: %d", ns);
  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    poly_tomsg(msg, &ap);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("poly_tomsg: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of poly_tomsg is: %d", ns);
  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    poly_frommsg(&ap, msg);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("poly_frommsg: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of poly_frommsg is: %d", ns);
  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    neon_ntt(ap.coeffs);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("neon_ntt: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of neon_ntt is: %d", ns);

  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    neon_invntt(ap.coeffs);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("neon_invntt: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of neon_invntt is: %d", ns);

  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    crypto_kem_keypair(pk, sk);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("crypto_kem_keypair: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of crypto_kem_keypair is: %d", ns);
  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    crypto_kem_enc(ct, key, pk);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("crypto_kem_enc: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of crypto_kem_enc is: %d", ns);


  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    crypto_kem_dec(key, ct, sk);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("crypto_kem_dec: %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of crypto_kem_dec is: %d", ns);

  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    VectorVectorMul(&ap, &sp, &b);
  }
  TIME(stop,"etime");
  ns = CALC(start, stop);
  printf("VectorVectorMul %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of VectorVectorMul is: %d", ns);

  TIME(start,"stime");
  for(i=0;i<NTESTS;i++) {
    MatrixVectorMul(matrix, &sp, &b);
  }
  TIME(stop,"stime");
  ns = CALC(start, stop);
  printf("MatrixVectorMul %lld\n", ns);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "The value of MatrixVectorMul is: %d", ns);



  return ns;
}
