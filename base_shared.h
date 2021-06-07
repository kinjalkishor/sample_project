#pragma once

#include <cstdio>
#include <cstdarg>



//va_list argptr;
//char text[1024];
//va_start (argptr, error);
//vsprintf (text, error, argptr);
//va_end (argptr);

#define q_va_vsprintf(buffer_name, buffer_size, msg) \
    va_list argptr;\
	char buffer_name[buffer_size];\
	va_start(argptr, msg);\
	vsprintf(buffer_name, msg, argptr);\
	va_end(argptr)


//MessageBoxW(NULL, L"text", L"Error", 0 /* MB_OK */ );
#define q_msg_boxw_ok(msg)		MessageBoxW(NULL, msg, L"Error", 0)
//#define q_msg_box_ok(msg)		MessageBoxW(NULL, flib::mb_towstr(msg), L"Error", 0)


//=========================
// Utility Functions
//=========================

// Safe Set nullptr
//#define q_safe_null(p)			{ if(p) { (p) = nullptr; } }


// Release COM objects safely
// ReleaseCOM(x)
//#undef SAFE_RELEASE
//#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p) = nullptr; } }



//#define ARRAY_SIZE(a)                               \
//  ((sizeof(a) / sizeof(*(a))) /                     \
//  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

// Number of elements in an array. NUMBER_OF, ARRSIZE, _countof, NELEM.
//#define Q_array_size2( array_name, type ) (sizeof(array_name)/sizeof(type))
//#define Q_array_size( array_name ) (sizeof(array_name)/sizeof(type))
// We never call _ArraySizeHelper, we just take the size of dereferencing its return type.
// We do not even implement _ArraySizeHelper, we just declare it.
// Attempts to pass pointers instead of arrays to this macro result in compile time errors.
template <class T, size_t N> char (&_ArraySizeHelper( T (&arr)[N]))[N];
#define q_array_size(arr) (sizeof( _ArraySizeHelper( arr ) ))