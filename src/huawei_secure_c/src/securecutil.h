/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reverved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1. 
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 * 	http://license.coscl.org.cn/MulanPSL 
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v1 for more details.  
 */

#ifndef SECURECUTIL_H_46C86578_F8FF_4E49_8E64_9B175241761F
#define SECURECUTIL_H_46C86578_F8FF_4E49_8E64_9B175241761F
#include "securec.h"

#if (defined(_MSC_VER)) && (_MSC_VER >= 1400)
#define SECUREC_MASK_MSVC_CRT_WARNING __pragma(warning(push)) \
    __pragma(warning(disable:4996 4127))
#define SECUREC_END_MASK_MSVC_CRT_WARNING  __pragma(warning(pop))
#else
#define SECUREC_MASK_MSVC_CRT_WARNING
#define SECUREC_END_MASK_MSVC_CRT_WARNING
#endif
#define SECUREC_WHILE_ZERO SECUREC_MASK_MSVC_CRT_WARNING while (0) SECUREC_END_MASK_MSVC_CRT_WARNING

#ifndef SECUREC_HAVE_STRNLEN
#if (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 700) || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L)
#if SECUREC_IN_KERNEL
#define SECUREC_HAVE_STRNLEN 0
#else
#if defined(__GLIBC__) && __GLIBC__ >= 2 && defined(__GLIBC_MINOR__) && __GLIBC_MINOR__ >= 10
#define SECUREC_HAVE_STRNLEN 1
#else
#define SECUREC_HAVE_STRNLEN 0
#endif
#endif
#else
#define SECUREC_HAVE_STRNLEN 0
#endif
#endif

#if SECUREC_IN_KERNEL
/* in kernel disbale functions */
#ifndef SECUREC_ENABLE_SCANF_FILE
#define SECUREC_ENABLE_SCANF_FILE 0
#endif
#ifndef SECUREC_ENABLE_SCANF_FLOAT
#define SECUREC_ENABLE_SCANF_FLOAT 0
#endif
#ifndef SECUREC_ENABLE_SPRINTF_FLOAT
#define SECUREC_ENABLE_SPRINTF_FLOAT 0
#endif
#ifndef SECUREC_HAVE_MBTOWC
#define SECUREC_HAVE_MBTOWC 0
#endif
#ifndef SECUREC_HAVE_WCTOMB
#define SECUREC_HAVE_WCTOMB 0
#endif
#ifndef SECUREC_HAVE_WCHART
#define SECUREC_HAVE_WCHART 0
#endif
#else /* no in kernel */
/* Systems that do not support file, can define this macro to 0. */
#ifndef SECUREC_ENABLE_SCANF_FILE
#define SECUREC_ENABLE_SCANF_FILE 1
#endif
#ifndef SECUREC_ENABLE_SCANF_FLOAT
#define SECUREC_ENABLE_SCANF_FLOAT 1
#endif
/* Systems that do not support float, can define this macro to 0. */
#ifndef SECUREC_ENABLE_SPRINTF_FLOAT
#define SECUREC_ENABLE_SPRINTF_FLOAT 1
#endif
#ifndef SECUREC_HAVE_MBTOWC
#define SECUREC_HAVE_MBTOWC 1
#endif
#ifndef SECUREC_HAVE_WCTOMB
#define SECUREC_HAVE_WCTOMB 1
#endif
#ifndef SECUREC_HAVE_WCHART
#define SECUREC_HAVE_WCHART 1
#endif
#endif


#define SECUREC_INT_MAX                     2147483647
#define SECUREC_MUL_SIXTEEN(x)              ((x) << 4)
#define SECUREC_MUL_EIGHT(x)                ((x) << 3)
#define SECUREC_MUL_TEN(x)                  ((((x) << 2) + (x)) << 1)
/* Limited format input and output width */
#define SECUREC_MAX_WIDTH_LEN_DIV_TEN       21474836
#define SECUREC_MAX_WIDTH_LEN               SECUREC_MUL_TEN(SECUREC_MAX_WIDTH_LEN_DIV_TEN)
/* Is the x multiplied by 10 greater than */
#define SECUREC_MUL_TEN_ADD_BEYOND_MAX(x)   (((x) > SECUREC_MAX_WIDTH_LEN_DIV_TEN))

#define SECUREC_FLOAT_BUFSIZE               (309 + 40)  /* Max length of double value */
#define SECUREC_FLOAT_BUFSIZE_LB            (4932 + 40) /* Max length of long double value */
#define SECUREC_FLOAT_DEFAULT_PRECISION     6

/* This macro does not handle pointer equality or integer overflow */
#define SECUREC_MEMORY_NO_OVERLAP(dest, src, count) \
    (((src) < (dest) && ((const char *)(src) + (count)) <= (char *)(dest)) || \
    ((dest) < (src) && ((char *)(dest) + (count)) <= (const char *)(src)))

#define SECUREC_MEMORY_IS_OVERLAP(dest, src, count) \
    (((src) < (dest) && ((const char *)(src) + (count)) > (char *)(dest)) || \
    ((dest) < (src) && ((char *)(dest) + (count)) > (const char *)(src)))

/*
 * Check whether the strings overlap, len is the length of the string not include terminator
 * Length is related to data type char or wchar , do not force conversion of types
 */
#define SECUREC_STRING_NO_OVERLAP(dest, src, len) \
    (((src) < (dest) && ((src) + (len)) < (dest)) || \
    ((dest) < (src) && ((dest) + (len)) < (src)))

/*
 * Check whether the strings overlap for strcpy wcscpy function, dest len and src Len are not include terminator
 * Length is related to data type char or wchar , do not force conversion of types
 */
#define SECUREC_STRING_IS_OVERLAP(dest, src, len) \
    (((src) < (dest) && ((src) + (len)) >= (dest)) || \
    ((dest) < (src) && ((dest) + (len)) >= (src)))

/*
 * Check whether the strings overlap for strcat wcscat function, dest len and src Len are not include terminator
 * Length is related to data type char or wchar , do not force conversion of types
 */
#define SECUREC_CAT_STRING_IS_OVERLAP(dest, destLen, src, srcLen) \
    (((dest) < (src) && ((dest) + (destLen) + (srcLen)) >= (src)) || \
    ((src) < (dest) && ((src) + (srcLen)) >= (dest)))


#if SECUREC_HAVE_STRNLEN
#define SECUREC_CALC_STR_LEN(str, maxLen, outLen) do { \
    *(outLen) = strnlen((str), (maxLen)); \
} SECUREC_WHILE_ZERO
#define SECUREC_CALC_STR_LEN_OPT(str, maxLen, outLen) do { \
    if ((maxLen) > 8) { \
        /* Optimization or len less then 8 */ \
        if (*((str) + 0) == '\0') { \
            *(outLen) = 0; \
        } else if (*((str) + 1) == '\0') { \
            *(outLen) = 1; \
        } else if (*((str) + 2) == '\0') { \
            *(outLen) = 2; \
        } else if (*((str) + 3) == '\0') { \
            *(outLen) = 3; \
        } else if (*((str) + 4) == '\0') { \
            *(outLen) = 4; \
        } else if (*((str) + 5) == '\0') { \
            *(outLen) = 5; \
        } else if (*((str) + 6) == '\0') { \
            *(outLen) = 6; \
        } else if (*((str) + 7) == '\0') { \
            *(outLen) = 7; \
        } else if (*((str) + 8) == '\0') { \
            /* Optimization with a length of 8 */ \
            *(outLen) = 8; \
        } else { \
            /* The offset is 8 because the performance of 8 byte alignment is high */ \
            *(outLen) = 8 + strnlen((str) + 8, (maxLen) - 8); \
        } \
    } else { \
        SECUREC_CALC_STR_LEN((str), (maxLen), (outLen)); \
    } \
} SECUREC_WHILE_ZERO
#else
#define SECUREC_CALC_STR_LEN(str, maxLen, outLen) do { \
    const char *strEnd = (const char *)(str); \
    size_t availableSize = (size_t)(maxLen); \
    while (availableSize > 0 && *strEnd != '\0') { \
        --availableSize; \
        ++strEnd; \
    } \
    *(outLen) = (size_t)(strEnd - (str)); \
} SECUREC_WHILE_ZERO
#define SECUREC_CALC_STR_LEN_OPT SECUREC_CALC_STR_LEN
#endif

#define SECUREC_CALC_WSTR_LEN(str, maxLen, outLen) do { \
    const wchar_t *strEnd = (const wchar_t *)(str); \
    *(outLen) = 0; \
    while (*(outLen) < (maxLen) && *strEnd != L'\0') { \
        *(outLen) = *(outLen) + 1; \
        ++strEnd; \
    } \
} SECUREC_WHILE_ZERO


#ifdef SECUREC_FORMAT_OUTPUT_INPUT
#if defined(SECUREC_COMPATIBLE_WIN_FORMAT) || defined(__ARMCC_VERSION)
typedef __int64 SecInt64;
typedef unsigned __int64 SecUnsignedInt64;
#if defined(__ARMCC_VERSION)
typedef unsigned int SecUnsignedInt32;
#else
typedef unsigned __int32 SecUnsignedInt32;
#endif
#else
typedef unsigned int SecUnsignedInt32;
typedef long long SecInt64;
typedef unsigned long long SecUnsignedInt64;
#endif

#ifdef SECUREC_FOR_WCHAR
#if defined(SECUREC_VXWORKS_PLATFORM) && !defined(__WINT_TYPE__)
typedef wchar_t wint_t;
#endif
typedef wchar_t SecChar;
typedef wchar_t SecUnsignedChar;
typedef wint_t SecInt;
typedef wint_t SecUnsignedInt;
#else /*  no SECUREC_FOR_WCHAR */
typedef char SecChar;
typedef unsigned char SecUnsignedChar;
typedef int SecInt;
typedef unsigned int SecUnsignedInt;
#endif
#endif

/* Determine whether the address is 8-byte aligned
 * Some systems do not have uintptr_t type, so  use NULL to clear tool alarm 507
 */
#define SECUREC_ADDR_ALIGNED_8(addr) (SecIsAddrAligned8((addr), NULL) == 0)

/* If you define the memory allocation function,
 * you need to define the function prototype. You can define this macro as a header file.
 */
#if defined(SECUREC_MALLOC_PROTOTYPE)
SECUREC_MALLOC_PROTOTYPE
#endif

#ifndef SECUREC_MALLOC
#define SECUREC_MALLOC(x) malloc((size_t)(x))
#endif

#ifndef SECUREC_FREE
#define SECUREC_FREE(x)   free((void *)(x))
#endif

/* struct for performance */
typedef struct {
    unsigned char buf[1]; /* Performance optimization code structure assignment length 1 bytes */
} SecStrBuf1;
typedef struct {
    unsigned char buf[2]; /* Performance optimization code structure assignment length 2 bytes */
} SecStrBuf2;
typedef struct {
    unsigned char buf[3]; /* Performance optimization code structure assignment length 3 bytes */
} SecStrBuf3;
typedef struct {
    unsigned char buf[4]; /* Performance optimization code structure assignment length 4 bytes */
} SecStrBuf4;
typedef struct {
    unsigned char buf[5]; /* Performance optimization code structure assignment length 5 bytes */
} SecStrBuf5;
typedef struct {
    unsigned char buf[6]; /* Performance optimization code structure assignment length 6 bytes */
} SecStrBuf6;
typedef struct {
    unsigned char buf[7]; /* Performance optimization code structure assignment length 7 bytes */
} SecStrBuf7;
typedef struct {
    unsigned char buf[8]; /* Performance optimization code structure assignment length 8 bytes */
} SecStrBuf8;
typedef struct {
    unsigned char buf[9]; /* Performance optimization code structure assignment length 9 bytes */
} SecStrBuf9;
typedef struct {
    unsigned char buf[10]; /* Performance optimization code structure assignment length 10 bytes */
} SecStrBuf10;
typedef struct {
    unsigned char buf[11]; /* Performance optimization code structure assignment length 11 bytes */
} SecStrBuf11;
typedef struct {
    unsigned char buf[12]; /* Performance optimization code structure assignment length 12 bytes */
} SecStrBuf12;
typedef struct {
    unsigned char buf[13]; /* Performance optimization code structure assignment length 13 bytes */
} SecStrBuf13;
typedef struct {
    unsigned char buf[14]; /* Performance optimization code structure assignment length 14 bytes */
} SecStrBuf14;
typedef struct {
    unsigned char buf[15]; /* Performance optimization code structure assignment length 15 bytes */
} SecStrBuf15;
typedef struct {
    unsigned char buf[16]; /* Performance optimization code structure assignment length 16 bytes */
} SecStrBuf16;
typedef struct {
    unsigned char buf[17]; /* Performance optimization code structure assignment length 17 bytes */
} SecStrBuf17;
typedef struct {
    unsigned char buf[18]; /* Performance optimization code structure assignment length 18 bytes */
} SecStrBuf18;
typedef struct {
    unsigned char buf[19]; /* Performance optimization code structure assignment length 19 bytes */
} SecStrBuf19;
typedef struct {
    unsigned char buf[20]; /* Performance optimization code structure assignment length 20 bytes */
} SecStrBuf20;
typedef struct {
    unsigned char buf[21]; /* Performance optimization code structure assignment length 21 bytes */
} SecStrBuf21;
typedef struct {
    unsigned char buf[22]; /* Performance optimization code structure assignment length 22 bytes */
} SecStrBuf22;
typedef struct {
    unsigned char buf[23]; /* Performance optimization code structure assignment length 23 bytes */
} SecStrBuf23;
typedef struct {
    unsigned char buf[24]; /* Performance optimization code structure assignment length 24 bytes */
} SecStrBuf24;
typedef struct {
    unsigned char buf[25]; /* Performance optimization code structure assignment length 25 bytes */
} SecStrBuf25;
typedef struct {
    unsigned char buf[26]; /* Performance optimization code structure assignment length 26 bytes */
} SecStrBuf26;
typedef struct {
    unsigned char buf[27]; /* Performance optimization code structure assignment length 27 bytes */
} SecStrBuf27;
typedef struct {
    unsigned char buf[28]; /* Performance optimization code structure assignment length 28 bytes */
} SecStrBuf28;
typedef struct {
    unsigned char buf[29]; /* Performance optimization code structure assignment length 29 bytes */
} SecStrBuf29;
typedef struct {
    unsigned char buf[30]; /* Performance optimization code structure assignment length 30 bytes */
} SecStrBuf30;
typedef struct {
    unsigned char buf[31]; /* Performance optimization code structure assignment length 31 bytes */
} SecStrBuf31;
typedef struct {
    unsigned char buf[32]; /* Performance optimization code structure assignment length 32 bytes */
} SecStrBuf32;
typedef struct {
    unsigned char buf[33]; /* Performance optimization code structure assignment length 33 bytes */
} SecStrBuf33;
typedef struct {
    unsigned char buf[34]; /* Performance optimization code structure assignment length 34 bytes */
} SecStrBuf34;
typedef struct {
    unsigned char buf[35]; /* Performance optimization code structure assignment length 35 bytes */
} SecStrBuf35;
typedef struct {
    unsigned char buf[36]; /* Performance optimization code structure assignment length 36 bytes */
} SecStrBuf36;
typedef struct {
    unsigned char buf[37]; /* Performance optimization code structure assignment length 37 bytes */
} SecStrBuf37;
typedef struct {
    unsigned char buf[38]; /* Performance optimization code structure assignment length 38 bytes */
} SecStrBuf38;
typedef struct {
    unsigned char buf[39]; /* Performance optimization code structure assignment length 39 bytes */
} SecStrBuf39;
typedef struct {
    unsigned char buf[40]; /* Performance optimization code structure assignment length 40 bytes */
} SecStrBuf40;
typedef struct {
    unsigned char buf[41]; /* Performance optimization code structure assignment length 41 bytes */
} SecStrBuf41;
typedef struct {
    unsigned char buf[42]; /* Performance optimization code structure assignment length 42 bytes */
} SecStrBuf42;
typedef struct {
    unsigned char buf[43]; /* Performance optimization code structure assignment length 43 bytes */
} SecStrBuf43;
typedef struct {
    unsigned char buf[44]; /* Performance optimization code structure assignment length 44 bytes */
} SecStrBuf44;
typedef struct {
    unsigned char buf[45]; /* Performance optimization code structure assignment length 45 bytes */
} SecStrBuf45;
typedef struct {
    unsigned char buf[46]; /* Performance optimization code structure assignment length 46 bytes */
} SecStrBuf46;
typedef struct {
    unsigned char buf[47]; /* Performance optimization code structure assignment length 47 bytes */
} SecStrBuf47;
typedef struct {
    unsigned char buf[48]; /* Performance optimization code structure assignment length 48 bytes */
} SecStrBuf48;
typedef struct {
    unsigned char buf[49]; /* Performance optimization code structure assignment length 49 bytes */
} SecStrBuf49;
typedef struct {
    unsigned char buf[50]; /* Performance optimization code structure assignment length 50 bytes */
} SecStrBuf50;
typedef struct {
    unsigned char buf[51]; /* Performance optimization code structure assignment length 51 bytes */
} SecStrBuf51;
typedef struct {
    unsigned char buf[52]; /* Performance optimization code structure assignment length 52 bytes */
} SecStrBuf52;
typedef struct {
    unsigned char buf[53]; /* Performance optimization code structure assignment length 53 bytes */
} SecStrBuf53;
typedef struct {
    unsigned char buf[54]; /* Performance optimization code structure assignment length 54 bytes */
} SecStrBuf54;
typedef struct {
    unsigned char buf[55]; /* Performance optimization code structure assignment length 55 bytes */
} SecStrBuf55;
typedef struct {
    unsigned char buf[56]; /* Performance optimization code structure assignment length 56 bytes */
} SecStrBuf56;
typedef struct {
    unsigned char buf[57]; /* Performance optimization code structure assignment length 57 bytes */
} SecStrBuf57;
typedef struct {
    unsigned char buf[58]; /* Performance optimization code structure assignment length 58 bytes */
} SecStrBuf58;
typedef struct {
    unsigned char buf[59]; /* Performance optimization code structure assignment length 59 bytes */
} SecStrBuf59;
typedef struct {
    unsigned char buf[60]; /* Performance optimization code structure assignment length 60 bytes */
} SecStrBuf60;
typedef struct {
    unsigned char buf[61]; /* Performance optimization code structure assignment length 61 bytes */
} SecStrBuf61;
typedef struct {
    unsigned char buf[62]; /* Performance optimization code structure assignment length 62 bytes */
} SecStrBuf62;
typedef struct {
    unsigned char buf[63]; /* Performance optimization code structure assignment length 63 bytes */
} SecStrBuf63;
typedef struct {
    unsigned char buf[64]; /* Performance optimization code structure assignment length 64 bytes */
} SecStrBuf64;




/* User can change the error handler by modify the following definition,
 * such as logging the detail error in file.
 */
#if defined(_DEBUG) || defined(DEBUG)
#if defined(SECUREC_ERROR_HANDLER_BY_ASSERT)
#define SECUREC_ERROR_INVALID_PARAMTER(msg) assert(msg "invalid argument" == NULL)
#define SECUREC_ERROR_INVALID_RANGE(msg)    assert(msg "invalid dest buffer size" == NULL)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   assert(msg "buffer overlap" == NULL)
#elif defined(SECUREC_ERROR_HANDLER_BY_PRINTF)
#if SECUREC_IN_KERNEL
#define SECUREC_ERROR_INVALID_PARAMTER(msg) printk("%s invalid argument\n", msg)
#define SECUREC_ERROR_INVALID_RANGE(msg)    printk("%s invalid dest buffer size\n", msg)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   printk("%s buffer overlap\n", msg)
#else
#define SECUREC_ERROR_INVALID_PARAMTER(msg) printf("%s invalid argument\n", msg)
#define SECUREC_ERROR_INVALID_RANGE(msg)    printf("%s invalid dest buffer size\n", msg)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   printf("%s buffer overlap\n", msg)
#endif
#elif defined(SECUREC_ERROR_HANDLER_BY_FILE_LOG)
#define SECUREC_ERROR_INVALID_PARAMTER(msg) LogSecureCRuntimeError(msg " EINVAL\n")
#define SECUREC_ERROR_INVALID_RANGE(msg)    LogSecureCRuntimeError(msg " ERANGE\n")
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   LogSecureCRuntimeError(msg " EOVERLAP\n")
#else /* no HANDLER is defined */
#define SECUREC_ERROR_INVALID_PARAMTER(msg) ((void)0)
#define SECUREC_ERROR_INVALID_RANGE(msg)    ((void)0)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   ((void)0)
#endif
#else /* no DEBUG */
#define SECUREC_ERROR_INVALID_PARAMTER(msg) ((void)0)
#define SECUREC_ERROR_INVALID_RANGE(msg)    ((void)0)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg)   ((void)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* assembly language memory copy and memory set for X86 or MIPS ... */
#ifdef SECUREC_USE_ASM
    extern void *memcpy_opt(void *, const void *, size_t);
    extern void *memset_opt(void *, int, size_t);
#endif

#if defined(SECUREC_ERROR_HANDLER_BY_FILE_LOG)
    extern void LogSecureCRuntimeError(const char *errDetail);
#endif

#ifdef SECUREC_INLINE_DO_MEMCPY
static void SecDoMemcpy(void *dest, const void *src, size_t count)
{
    /*
     * if SECUREC_USE_ASM macro is enabled, it will call assembly language function to improve performance.
     */
#ifdef SECUREC_USE_ASM
    (void)memcpy_opt(dest, src, count);
#else
    /* large enough, let system API do it */
    (void)memcpy(dest, src, count);
#endif
}
#endif

#ifdef SECUREC_INLINE_DO_MEMSET
static void SecDoMemset(void *dest, int c, size_t count)
{
#ifdef SECUREC_USE_ASM
    (void)memset_opt(dest, c, count);
#else
    (void)memset(dest, c, count);
#endif
}
#endif

#ifdef SECUREC_INLINE_STR_LEN
/* The function compiler will be inlined and not placed in other files */
static size_t SecStrMinLen(const char *str, size_t maxLen)
{
    size_t len;
    SECUREC_CALC_STR_LEN(str, maxLen, &len);
    return len;
}
#endif

#ifdef SECUREC_INLINE_STR_LEN_OPT
/* The function compiler will be inlined and not placed in other files */
static size_t SecStrMinLenOpt(const char *str, size_t maxLen)
{
    size_t len;
    SECUREC_CALC_STR_LEN_OPT(str, maxLen, &len);
    return len;
}
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

