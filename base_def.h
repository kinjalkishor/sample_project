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

//============================
// Basic Types
//============================

#include <limits>
//#include <float.h>

// CHECK: using better than typedef

// On 64 bit windows platforms.
// int, long - 32 bit
// ULONG - 32 bit, use portable ULONG_PTR instead
// Pointers - 64 bit, pointer value truncated if assigned to a 32-bit variable.
// size_t, time_t, ptrdiff_t - 64 bit, check if int is processes as these and then truncated when passed back as int.
// %x in printf works on only first 32 bits, use %I32x (32 bit), %I64x (64 bit). %p (hex format for a pointer) will work as expected.
// A 32-bit unsigned negative number becomes a large 64-bit positive number, declare variable as a signed value or explicitly typecast it to LONG.

// Alignment (1 byte is 8 bits) - Byte – 8 bits, Word – 16 bits, Double Word – 32 bits, Quad Word – 64 bits, Octa Word – 128 bits.
// int32 can store 32 bit values or 32 flags.

#if defined(_WINDOWS)
	#if defined(_MSC_VER)

			using int8	= signed __int8;
			using uint8 = unsigned __int8;
			using int16 = signed __int16;
			using uint16 = unsigned __int16;
			using int32 = signed __int32;				// long int					// max_size 2 billion
			using uint32 = unsigned __int32;			// unsigned long int
			using int64 = signed __int64;				// long long int
			using uint64 = unsigned __int64;			// unsigned long long int
	#else
			using int8 = signed char;
			using uint8 = unsigned char;
			using int16 = signed short int;
			using uint16 = unsigned short int;
			using int32 = signed long int;		
			using uint32 = unsigned long int;		
			using int64 = signed long long int;
			using uint64 = unsigned long long int;
	#endif
#endif


//============================
// User Defined Types
//============================

using byte = uint8;					// 8-bit unsigned.

#include <cstdint>
// index types, maximum int size provided by system
// On 32 bit system 2^31 int32 type char array(1 byte unit) will take 16GB RAM
// On 64 bit system 2^63 int64 type char array(1 byte unit) will take 68719476736 GB of Ram
//usize holds numbers as large as the address space
using usize = uintmax_t;	//uint64;	 //size_t
using isize = intmax_t;		//int64;	 //ssize_t //ptrdiff_t
//using index_t = isize;		//ptrdiff_t;

// Data type size:
//char			1 byte
//short			2 bytes
//int			4 bytes	
//long			4 bytes (8 bytes on other 64 bit OS LP64, Windows64 is LLP64)
//long long		8 bytes		
//float			4 bytes
//double		8 bytes
//long double	16 bytes
// Pointers 8 bytes (64-bit)
//intptr_t		Signed integer of size equal to a pointer
//uintptr_t		Unsigned integer of size equal to a pointer
//size_t, time_t, and ptrdiff_t 64-bit
//intmax_t		Biggest size of integer on the platform (might be larger than int64_t)
//time_t		64-bit

using uchar = uint8;
//using ushort = uint16;
using uint = uint32;


// used in math functions
using llint = signed long long int;
using ullint = unsigned long long int;
using half16 = uint16;		// 16-bit float


//typedef uint16			word;					// 16-bit unsigned, word.
//typedef uint32			dword;					// 32-bit unsigned, double word.
//typedef uint64			qword;					// 64-bit unsigned, quad word.
// Windows defines
//typedef int                 BOOL;
//typedef unsigned char       BYTE;
//typedef unsigned short	  WORD;
//typedef unsigned long       DWORD;
//typedef unsigned __int64	  DWORDLONG;
// windows DWORDLONG is ULONGLONG or uint64. DWORD is uint32
//typedef __int64 LONGLONG;	//LL
//typedef unsigned __int64 ULONGLONG; //ULL

constexpr char k_null_char = '\0';

//======================================
// MISC
//======================================

#define forloop(v, m)				for(int v = 0; v < int(m); ++v)
//#define forloop_rev(v, m)			for(int v = int(m); --v >= 0;)
//#define forloop_t(type, v, m)		for(type v = 0; v < type(m); ++v)
//#define forloop_isize(v, m)			for(isize v = 0; v < isize(m); ++v)

#define forloop_step(v, m, step)	for(int v = 0; v < m; i += step)

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


//=========================
// ERROR Handling
//=========================
template<class T>
class fresult
{
public:
	bool success = true;
    const char* msg = nullptr;
    T val;

    // Success case
    fresult(T val) { this->val = val; }

    // Error case
    fresult(T default_val, const char* err_msg)
    {
        this->success = false;
        this->msg = err_msg;
        this->val = default_val;        
    }

    bool failed() { return !success; }
};


#define q_finfo(msg)		(__FUNCTION__": "  #msg)


//=========================
// Math Types
//=========================
namespace gm
{


template<class T>
class tvec3
{
public:
	union
    {
		struct { T x, y, z; };
		T e[3];
    };		

	constexpr int size() const { return 3; }

	tvec3() = default;
	//tvec3() : x(scast<T>(0)), y(scast<T>(0)), z(scast<T>(0)) {}
	explicit tvec3(T f) : x(f), y(f), z(f) {}	
	tvec3(T x, T y, T z) : x(x), y(y), z(z) {}	
		
	const T* data() const				{ return &e[0]; }
	T* data()							{ return &e[0]; }
	const T& operator[] (int i) const	{ return e[i]; }
    T& operator [] (int i)				{ return e[i]; }
};

using vec3 = tvec3<float>;
using vec3i = tvec3<int>;
using vec3u = tvec3<uint>;
using vec3d = tvec3<double>;

} //gm


namespace flib
{


size_t strlcpy(char* dest, const char* src, size_t dest_size);
size_t strlcat(char* dest, const char* src, size_t dest_size);


//======================================
// char*, utf-8 conversion
//======================================
const wchar_t* mb_towstr(const char* utf8_str);
const char* mb_tostr(const wchar_t* wchar_str);


} //flib
