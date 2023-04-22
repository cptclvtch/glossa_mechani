#if defined(__GNUC__) || defined(__TINYC__)
#ifdef VERBOSE
#warning You're in luck! Your compiler uses the Labels as Values extension. The switch loop will be replaced with a jump table.
#endif
#define __labels_as_values__
#endif

#ifdef __cplusplus
#include <cstdint>
using std::uint32_t;
#else
#include <stdint.h>
#endif
	
#ifndef _WIN32
#include <sys/mman.h>
#include <errno.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __unix__
#endif

#ifdef __APPLE__
#include <stddef.h>
#endif

#ifdef TARGET_OS_IPHONE
#endif

#ifdef __ANDROID__
#endif

#ifdef XBOXONE
#endif

#if defined INCLUDE_PRINTING ||  defined CLT
#ifdef __ANDROID__
    #include <android/log.h>
    #define PRINT_FN(...) __android_log_print(ANDROID_LOG_VERBOSE, "|", __VA_ARGS__)
#else
    #ifdef __cplusplus
        #ifndef _GLIBCXX_CSTDIO
        #include <cstdio>
        #endif
    #else
        #ifndef printf
        int printf(const char* format, ...);
        #endif
        #ifndef getchar
        int getchar(void);
        #endif
    #endif
    #define PRINT_FN(...) printf(__VA_ARGS__)
#endif
#endif