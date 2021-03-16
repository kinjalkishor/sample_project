#include "base_def.h"

#include <cstring>
#include <cstdlib>

namespace flib
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
// string, wstring, utf-8 conversion
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