
#include <cstring>

#include <string>
#include <sstream>
#include <fstream>


#include "base_def.h"
#include "base_debug.h"
#include "base_iostream.h"

//#define NW_APP_NAME	L"NexWars"

#if _MSC_VER
// Inconsistent annotation for function: this instance has an error
#pragma warning(disable : 28251)		

//libcmt.lib conflicts with use of other libs warning
#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
#endif


export module base_shared;

import base_def;



export namespace flib
{

constexpr float k_aspect_ratio_4_3    = scast<float>(1.33333333333333333333);
constexpr float k_aspect_ratio_16_9   = scast<float>(1.77777777777777777778);
bool aspect_ratio(int width, int height) 
{ 
    if (height == 0)
    {      
        // if height is 0, return most common aspect ratio, 
        // since division by zero is error
        q_debug("fn aspect_ratio: height is zero. Setting aspect ratio to 16:9\n");
        return k_aspect_ratio_16_9;
    }
    else
    {
        return (scast<float>(width)/scast<float>(height));
    }
}


//---------------------------------

//====================
// Char Functions
//====================
//bool char_str_ci_compare(const char* s1, const char* s2);

inline bool str_equals(const char* s1, const char* s2)
{
    return (!strcmp(s1, s2));
}

inline bool str_equals_ci(const char* s1, const char* s2)
{
    return (!_strcmpi(s1, s2));
}



//----------------------
#if 0
// Returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by str1. 
// The returned pointer must be passed to free to avoid a memory leak. 
//char *s2 = strdup(s1); free(s2);
//	$OpenBSD: strdup.c,v 1.7 2015/08/31 02:53:57 guenther Exp $	
char* strdup(const char *str)
{
	size_t len;
	char *copy;

	len = strlen(str) + 1;

	if ((copy = (char*)malloc(len)) == nullptr)
	{
		return(nullptr);
	}

	(void)memcpy(copy, str, len);
	return(copy);
}
#endif



// May overrun the buffer: strcpy, sprintf
// Sometimes null-terminates: strncpy, _snprintf, swprintf, wcsncpy, lstrcpy
// Always null-terminates: snprintf, strlcpy
// strncpy: copies the first num characters of source to destination

// Always null terminates at maximum len-1 characters if src is greater than dest
// snprintf guarantees null-termination, but strncpy and _snprintf do not
// openbsd implementation can also be used

// strlcpy() take the full size of the destination buffer and guarantee NULL-termination if there is room.
// pass dest_len as length if want to fill dest buffer to end by trimming src if src is bigger.

// Buffer safe and null termination 
// strlcpy() copies up to dstsize-1 characters from the string src to dst,
// NULL-terminating the result, if dstsize is not 0.
// dest_size = strlen(dest) + 1
//inline size_t str_copyz(char* dest, const char* src, size_t dest_size)
//{
//    return strlcpy(dest, src, dest_size);
//}
//
//inline size_t str_concatz(char* dest, const char* src, size_t dest_size)
//{
//    return strlcat(dest, src, dest_size);
//}



// string s = File.ReadAllText(filename);
// TextFileRead loads in a standard text file from a given filename and then returns it as a string.
bool string_from_file(std::string& out_string, const char *file_name)
{
#if 0

	// Using getline
	// A string for holding the current line
	std::string line = std::string(); 

	// Open an input stream with the selected file
	std::ifstream filesrc_stream( file_name, std::ios::in ); 
	if (filesrc_stream.is_open()) 
	{
		// If the file opened successfully
		while (!filesrc_stream.eof()) 
		{ 
			// While we are not at the end of the file
			std::getline(filesrc_stream, line); // Get the current line
		  	out_string.append(line); // Append the line to our file string
			out_string.append("\n"); // Append a new line character
		}
		filesrc_stream.close(); // Close the file
	}
	else
	{
		//print("Cannot open input file: {}\n", file_name);
		return false;
	}


#else

	// Read the text from the file.
	// Open file.
	//std::ifstream filesrc_stream;
	//filesrc_stream.open(file_name);

	// Open file using constructor
	std::ifstream filesrc_stream(file_name, std::ios::in);

	//if (!filesrc_stream) { return false; }
	// Most vexing parse problem if () is removed surrounding 2nd parameter
	// TimeKeeper time_keeper(Timer()); is variable declaration or function declaration
	// programmer expect variable declaration but compiler interprets as function declaration
	//std::string out_string = std::string(std::istreambuf_iterator<char>(filesrc_stream), (std::istreambuf_iterator<char>()));
	// Uniform initialization syntax of C++11 solves Most vexing parse problem
	//std::string out_string{std::istreambuf_iterator<char>{filesrc_stream}, {}};
	//filesrc_stream.close();


	if (filesrc_stream.is_open())
	{
#if 1
		// second fastest
		std::stringstream sstr;
		// Read file's buffer contents into streams.
		// Read file_name file stream in string stream. 
		sstr << filesrc_stream.rdbuf();		
		filesrc_stream.close();
		// Convert stream into string
		// Save string stream in std::string out_string
		out_string = sstr.str();
#else

		// fastest 
		filesrc_stream.seekg(0, std::ios::end);
		out_string.resize(filesrc_stream.tellg());
		filesrc_stream.seekg(0, std::ios::beg);
		filesrc_stream.read(&out_string[0], out_string.length());

		// slowest
		//filesrc_stream.seekg(0, std::ios::end);
		//out_string.reserve(filesrc_stream.tellg());
		//filesrc_stream.seekg(0, std::ios::beg);
		//out_string.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		//slow
		//filesrc_stream.seekg( 0, std::ios_base::end );
		//const std::streampos pos = filesrc_stream.tellg();
		//filesrc_stream.seekg(0, std::ios_base::beg);
		//if( pos!=std::streampos(-1) ) { out_string.reserve(static_cast<std::string::size_type>(pos)); }
		//out_string.assign(std::istream_iterator<char>(file), std::istream_iterator<char>());	
#endif
	}
	else
	{
		print("Cannot open input file: %s\n", file_name);
		return false;
	}

#endif

	return true;
}


//======================================
// string, wstring, utf-8 conversion
//======================================
//std::wstring mb_towstr(const std::string& utf8_str);
//std::string mb_tostr(const std::wstring& wchar_str);

};


//========================================================


//======================================
// 3d Math
//======================================
export namespace gm
{
//===============================
// Integer Packing Unpacking
//===============================

// Packs uint a, b, c, d [0-255] components in a uint.
// Maps unsigned 8 bits/channel to UColor.
// RGBA format
uint pack_uint(uint a, uint b, uint c, uint d)
{
	return ((uint)(a) << 24)|((uint)(b) << 16)|((uint)(c) << 8)|((uint)(d));
}

// Unpacks four uint8 components out of uint and assign to uint.
void unpack_uint(uint val, uint& a, uint& b, uint& c, uint& d)
{
	(a) = (uint)((val)>>24);
	(b) = (uint)((val)>>16);
	(c) = (uint)((val)>>8);
	(d) = (uint)(val);
}


//====================
// Color Functions
//====================
#if 0
// maps unsigned 8 bits/channel to D3DCOLOR
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_XYUV(y,u,v)   D3DCOLOR_ARGB(0xff,y,u,v)
#define D3DCOLOR_AYUV(a,y,u,v) D3DCOLOR_ARGB(a,y,u,v)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f), (DWORD)((g)*255.f), (DWORD)((b)*255.f), (DWORD)((a)*255.f))
#endif

// float to uint component of a packed uint.
//#define Q_FTOUC( val )		( (uint)((val)*255.f)&0xff )

// float to uint component of a packed uint.
uint ftouc(float val)
{
	//return ((uint)((val)*255.f)&0xff);
	return (val >= 1.0f ? 0xff : val <= 0.0f ? 0x00 : (uint) (val * 255.0f + 0.5f));
}

// Multiply with this to get float value in [0-1.0] from a component of packed uint. (1.0 / 255.0)
constexpr float k_uc_inv = scast<float>(0.003921568627);
//static const float k_uc_inv;
//template <class float> const float k_uc_inv<float>	= (0.003921568627);	//in cpp file

// Packs float a, b, c, d [0-1.0] components in a uint.
// ARGB format
uint packf_uint(float a, float b, float c, float d)
{
	return ((ftouc(a) << 24) | (ftouc(b) << 16) | (ftouc(c) << 8) | (ftouc(d)));
}


// Unpacks four uint8 components out of uint and assign to floats.
void unpackf_uint(uint val, float& a, float& b, float& c, float& d)
{
	(a) = (((uint8)((val)>>24)) * scast<float>(k_uc_inv));
	(b) = (((uint8)((val)>>16)) * scast<float>(k_uc_inv));
	(c) = (((uint8)((val)>>8)) * scast<float>(k_uc_inv));
	(d) = (((uint8)(val)) * scast<float>(k_uc_inv));
}


// Supply arguments in order of name to packf_uint function
uint to_rgba(float r, float g, float b, float a)
{
	return packf_uint(r, g, b, a);
}

uint to_argb(float r, float g, float b, float a)
{
	return packf_uint(a, r, g, b);
}


// Same as RGB macro of Windows. Packs color in format of Win32 Api.
uint to_xbgr(float r, float g, float b, float a)
{
	return packf_uint(scast<float>(0), b, g, r);
}

uint argb_to_abgr(uint argb)
{
	byte A = (argb >> 24) & 0xff;
	byte R = (argb >> 16) & 0xff;
	byte G = (argb >>  8) & 0xff;
	byte B = (argb >>  0) & 0xff;

	return ((A << 24)|(B << 16)|(G << 8)|(R << 0));
}

}