#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>

export module base_def;


#ifdef _WIN32
#pragma warning(disable : 6031)		// truncation from const double to float
// a module declaration can appear only at the start of a translation unit unless a global module fragment is used
#pragma warning(disable : 5201)		
#endif


//============================
// Basic Types
//============================

//#include <limits>
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

			export using int8	= signed __int8;
			export using uint8 = unsigned __int8;
			export using int16 = signed __int16;
			export using uint16 = unsigned __int16;
			export using int32 = signed __int32;				// long int					// max_size 2 billion
			export using uint32 = unsigned __int32;			// unsigned long int
			export using int64 = signed __int64;				// long long int
			export using uint64 = unsigned __int64;			// unsigned long long int
	#else
			export using int8 = signed char;
			export using uint8 = unsigned char;
			export using int16 = signed short int;
			export using uint16 = unsigned short int;
			export using int32 = signed long int;		
			export using uint32 = unsigned long int;		
			export using int64 = signed long long int;
			export using uint64 = unsigned long long int;
	#endif
#endif


//============================
// User Defined Types
//============================

export using byte = uint8;					// 8-bit unsigned.

//#include <cstdint>
// index types, maximum int size provided by system
// On 32 bit system 2^31 int32 type char array(1 byte unit) will take 16GB RAM
// On 64 bit system 2^63 int64 type char array(1 byte unit) will take 68719476736 GB of Ram
//uintsz holds numbers as large as the address space
export using intsz = intmax_t;		//int64;	 //ssize_t //ptrdiff_t //isize
export using uintsz = uintmax_t;	//uint64;	 //size_t //usize
//using index_t = intsz;		//ptrdiff_t;

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

export using uchar = uint8;
//using ushort = uint16;
export using uint = uint32;


// used in math functions
export using llint = signed long long int;
export using ullint = unsigned long long int;
export using half16 = uint16;		// 16-bit float


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

//constexpr char k_null_char = '\0'; //.h
export inline const char k_null_char = '\0';


//=========================
// Math Types
//=========================
export namespace gm
{

class vrect
{
public:
	int x, y, w, h;
};

class vidinfo
{
public:
	int width = 0;
    int height = 0;			
    bool fullscreen = false;
};


template<class T>
class tvec2
{
public:
	union
    {
		struct { T x, y; };
		T e[2];
    };	

	constexpr int size() const { return 2; }	

	tvec2() = default;
	//tvec2() : e { {scast<T>(0)}, {scast<T>(0)} } {}
	explicit tvec2(T f) : e { {f}, {f} } {}	
	tvec2(T x, T y) : e { {x}, {y} } {}	
	
	const T* data() const				{ return &e[0]; }
	T* data()							{ return &e[0]; }
	const T& operator[] (int i) const	{ return e[i]; }
    T& operator [] (int i)				{ return e[i]; }
};

using vec2 = tvec2<float>;
using vec2i = tvec2<int>;
using vec2u = tvec2<uint>;
using vec2d = tvec2<double>;


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
	//tvec3() : e { {scast<T>(0)}, {scast<T>(0)}, {scast<T>(0)} } {}
	explicit tvec3(T f) : e { {f}, {f}, {f} } {}	
	tvec3(T x, T y, T z) : e { {x}, {y}, {z} } {}	
	
	const T* data() const				{ return &e[0]; }
	T* data()							{ return &e[0]; }
	const T& operator[] (int i) const	{ return e[i]; }
    T& operator [] (int i)				{ return e[i]; }
};

using vec3 = tvec3<float>;
using vec3i = tvec3<int>;
using vec3u = tvec3<uint>;
using vec3d = tvec3<double>;

template<class T>
class tvec4
{
public:
	union
    {
		struct { T x, y, z, w; };
		T e[4];
    };	

	constexpr int size() const { return 4; }	

	tvec4() = default;
	//tvec4() : e { {scast<T>(0)}, {scast<T>(0)}, {scast<T>(0)}, {scast<T>(0)} } {}
	explicit tvec4(T f) : e { {f}, {f}, {f}, {f} } {}	
	tvec4(T x, T y, T z, T w) : e { {x}, {y}, {z}, {w} } {}	
	
	const T* data() const				{ return &e[0]; }
	T* data()							{ return &e[0]; }
	const T& operator[] (int i) const	{ return e[i]; }
    T& operator [] (int i)				{ return e[i]; }
};

using vec4 = tvec4<float>;
using vec4i = tvec4<int>;
using vec4u = tvec4<uint>;
using vec4d = tvec4<double>;


class colorf
{
public:
	union
    {
		struct { float r, g, b, a; };
		float e[4];
    };	

	constexpr int size() const { return 4; }	

	colorf() = default;
	//colorf() : e { {scast<T>(0)}, {scast<T>(0)}, {scast<T>(0)}, {scast<T>(0)} } {}
	explicit colorf(float f) : e { {f}, {f}, {f}, {f} } {}	
	colorf(float r, float g, float b, float a) : e { {r}, {g}, {b}, {a} } {}	
	
	const float* data() const				{ return &e[0]; }
	float* data()							{ return &e[0]; }
	const float& operator[] (int i) const	{ return e[i]; }
    float& operator [] (int i)				{ return e[i]; }
};

} //gm


export namespace flib
{

//====================
// HASH Functions
//====================
// Fowler/Noll/Vo (FNV) hash function, variant 1a 
// default values recommended by isthe.com/chongo/tech/comp/fnv/
constexpr uint32_t Prime = 0x01000193; //   16777619
constexpr uint32_t Seed  = 0x811C9DC5; // 2166136261

// hash a C-style string
uint32_t fnv1a_hash(const char* text)
{
    uint32_t hash = Seed;
    //assert(text);
    const unsigned char* ptr = (const unsigned char*)text;
    while (*ptr)
    {
        hash = (*ptr++ ^ hash) * Prime;
        // same as hash = fnv1a(*ptr++, hash); but much faster in debug mode
    }
    return hash;
}

uint32 get_hash(const char* text)
{
	return fnv1a_hash(text);
}
//----------------------------------------


//returns x in [min_val, max_val]
template<class T>
inline T clamp(const T& x, const T& min_val, const T& max_val)
{
    //return minf(maxf(x, min_val), max_val); //irr

    //return std::clamp<T>(x, min_val, max_val);

    if (x < min_val) { return min_val; }
    if (x > max_val) { return max_val; }
    return x;       
}

// is x in [min_val, max_val)
inline bool is_inrange(intsz x, intsz min_val, intsz max_val) 
{
	return (x>=min_val && x<max_val); 
	//if ((x < min_val) || (x >= max_val)) { return false; }
	//return true;
}


// operator= needs to be overloaded for non pod types
template <class T>
inline void swap(T& a, T& b)
{
    const T t = a;
	a = b;
	b = t;
}


template<class T>
inline T minf(const T a, const T b)
{
	return (a < b) ? a : b;
}

template<class T>
inline T maxf(const T a, const T b)
{
	return (a > b) ? a : b;
}

template< class T > inline 
T min3(const T a, const T b, const T c)
{
	return minf(minf(a, b), c);
}

template< class T > inline 
T max3(const T a, const T b, const T c)
{
	return maxf(maxf(a, b), c);
}

//template<class T>
//inline T bound(T a, T b, T c) 
//{
//    return maxf(a, minf(b, c));
//}



//-----------------------------------
#if 0
//use strlcpy instead
inline void strncpyz(char *dest, const char *src, int destsize) 
{
	strncpy(dest, src, destsize-1);
	dest[destsize-1] = 0;
}
#endif

// $OpenBSD: strlcpy.c,v 1.16 2019/01/25 00:19:25 millert Exp $
// Copy string src to buffer dst of size dsize. At most dsize-1
// chars will be copied. Always NUL terminates (unless dsize == 0).
// Returns strlen(src); if retval >= dsize, truncation occurred.
//size_t strlcpy(char *dst, const char *src, size_t dsize)

size_t strlcpy(char* dest, const char* src, size_t dest_size)
{
	const char *osrc = src;
	size_t nleft = dest_size;

	/* Copy as many bytes as will fit. */
	if (nleft != 0)
	{
		while (--nleft != 0)
		{
			if ((*dest++ = *src++) == '\0')
				break;
		}
	}

	/* Not enough room in dest, add NULL and traverse rest of src. */
	if (nleft == 0)
	{
		if (dest_size != 0)
			*dest = '\0';		/* NULL-terminate dest */
		while (*src++)
			;
	}

	return(src - osrc - 1);	/* count does not include NULL */
}



// $OpenBSD: strlcat.c,v 1.19 2019/01/25 00:19:25 millert Exp $
// Appends src to string dst of size dsize (unlike strncat, dsize is the
// full size of dst, not space left). At most dsize-1 characters
// will be copied. Always NUL terminates (unless dsize <= strlen(dst)).
// Returns strlen(src) + MIN(dsize, strlen(initial dst)).
// If retval >= dsize, truncation occurred.
//size_t strlcat(char *dst, const char *src, size_t dsize)

size_t strlcat(char* dest, const char* src, size_t dest_size)
{
	const char *odst = dest;
	const char *osrc = src;
	size_t n = dest_size;
	size_t dlen;

	/* Find the end of dest and adjust bytes left but don't go past end. */
	while (n-- != 0 && *dest != '\0')
		dest++;
	dlen = dest - odst;
	n = dest_size - dlen;

	if (n-- == 0)
		return(dlen + strlen(src));
	while (*src != '\0')
	{
		if (n != 0)
		{
			*dest++ = *src;
			n--;
		}
		src++;
	}
	*dest = '\0';

	return(dlen + (src - osrc));	/* count does not include NULL */
}




//======================================
// char*, string, wstring, utf-8 conversion
//======================================

// no corresponding delete to this new
const wchar_t* mb_towstr(const char* utf8_str)
{
	size_t size = strlen(utf8_str) + 1;
	wchar_t* temp_str = new wchar_t[size];
	mbstowcs(temp_str, utf8_str, size);
	return temp_str;
}

const char* mb_tostr(const wchar_t* wchar_str)
{
	size_t size = wcslen(wchar_str) + 1;
	char* temp_str = new char[size];
	wcstombs(temp_str, wchar_str, size);
	return temp_str;
}


} //flib



//=========================
// ERROR Handling
//=========================
export template<class T>
class fresult
{
public:
	static const int buf_size = 256;
	bool success = true;
	char msg[buf_size] = {};
    T val;

    // Success case
    fresult(T val) { this->val = val; }

    // Error case
    fresult(T default_val, const char* err_msg)
    {
        this->success = false;
		flib::strlcpy(this->msg, err_msg, buf_size);
        this->val = default_val;        
    }

    bool failed() { return !success; }
};