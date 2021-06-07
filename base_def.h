#pragma once

//#if _MSC_VER
// Specify in preprocessor settings

// msvc compiler warnings for sscanf_s non standard msvc extensions
//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NONSTDC_NO_DEPRECATE

//#ifdef max
//	#undef max
//#endif
//#ifdef min
//	#undef min
//#endif
// Suppress the min and max definitions in Windef.h
//#define _NOMINMAX
//#endif




//======================================
// MISC
//======================================

#define forloopi(v, m)				for(int v = 0; v < int(m); ++v)
#define forloopi64(v, m)			for(int64 v = 0; v < int64(m); ++v)
#define forloopisz(v, m)			for(intsz v = 0; v < intsz(m); ++v)
//#define forloopi_rev(v, m)		for(int v = int(m); --v >= 0;)
//#define forloop_t(type, v, m)		for(type v = 0; v < type(m); ++v)


#define forloopi_step(v, m, step)	for(int v = 0; v < m; i += step)

#define scast						static_cast
#define dcast						dynamic_cast
#define rcast						reinterpret_cast
#define ccast						const_cast


//=========================
// Utility Functions
//=========================

//SecureZeroMemory
#define q_zero_memory(dest, length)		memset((dest), 0, (length))


// Safe Memory freeing.
//#undef SAFE_DELETE
#define q_safe_delete(p)			{ if(p) { delete (p);		(p) = nullptr; } }
#define q_safe_free(p)				{ if(p) { free(p);		(p) = nullptr; } }

// Memory allocated by new[] should always be free by delete[] or only one elment will be deleted by delete.
//#undef SAFE_DELETE_ARR
#define q_safe_delete_arr(p)		{ if(p) { delete[] (p);		(p) = nullptr; } }

//#define q_finfo(msg)		(__FUNCTION__": "  #msg)
#define q_finfo(...)		(__FUNCTION__": ",  __VA_ARGS__)


// BITSET
#define BIT(num)	(1ULL << (num))
// a=target variable, b=bit number to act upon 0-n
#define BIT_SET(a,b)	((a) |= (1ULL<<(b)))           
#define BIT_CLEAR(a,b)	((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b)	((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b)	(!!((a) & (1ULL<<(b))))        
// x=target variable, y=mask
#define BITMASK_SET(x,y)		((x) |= (y))
#define BITMASK_CLEAR(x,y)		((x) &= (~(y)))
#define BITMASK_FLIP(x,y)		((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y)	(!(~(x) & (y)))
#define BITMASK_CHECK_ANY(x,y)	((x) & (y))


//---





