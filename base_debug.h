#pragma once

#include <cstdio>

//=========================
// ERROR Print
//=========================
// Use like printf but first argument must be a format string.
#define q_debug(format, ...)		do { std::printf("%s: " format, __FUNCTION__, __VA_ARGS__); } while (0)
#define q_error(format, ...)		do { std::printf("ERROR: %s: " format, __FUNCTION__, __VA_ARGS__); } while (0)



// var should be fresult
#define q_result_check(var) \
if (var.failed()) { q_error("%s", var.msg); }


// Run time assert checking. Can disable for final release version.
void check_assert(const char *file, int line, const char* func, const char *expression, const char *msg);
#define Q_CFG_CHECK_ASSERTS
#if defined(Q_CFG_CHECK_ASSERTS)
//#define q_assert2(expression, msg)	if (!(expression)) check_assert(__FILE__, __LINE__, __FUNCTION__, #expression, msg)
#define q_assert2(expression, ...)		do { if (!(expression)) check_assert(__FILE__, __LINE__, __FUNCTION__, #expression, __VA_ARGS__); } while (0)
#else
#define q_assert2(expression, msg)
#endif
#define q_assert(expression)	q_assert2(expression, "\n")


//----------------------------------
//void debug_log(const char* label, const char* file, int line, const char* func, const char* msg);
//#define q_debug(msg)		debug_log("", __FILE__, __LINE__, __FUNCTION__, #msg)
//#define q_error(msg)		debug_log("ERROR: ", __FILE__, __LINE__, __FUNCTION__, msg)
//#define q_debug(...)		do { debug_log("", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); } while (0)
//#define q_error(...)		do { debug_log("ERROR: ", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); } while (0)

//#define q_debug(format, ...)		do { std::printf("%s: (%d), %s: " format, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); } while (0)
//#define q_error(format, ...)		do { std::printf("ERROR: %s: (%d), %s: " format, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__); } while (0)
// Example Usage:
//int x =1, y=2, sum =3;
//q_debug("%d + %d == %d\n", x, y, sum);
//q_error("%d + %d == %d\n", x, y, sum);
//q_debug("Hi Debug %d \n", x);
////std::printf("%s: %d, %s", __FILE__, __LINE__, __FUNCTION__);

