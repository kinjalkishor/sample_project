//#include "base_iostream.h"
#include "base_debug.h"



//=========================
// ERROR Print
//=========================
//---
#if 0
void debug_log(const char* label, const char* file, int line, const char* func, const char* msg)
{
	//std::printf("%s%s: %s", label, func, msg);
    //std::cout << label << func << ": " << msg; 	 
	print("{}{}: {}", label, func, msg); 	 
}
#endif

void check_assert(const char *file, int line, const char* func, const char *expression, const char *msg)
{
	std::printf("ASSERT FAILED: %s(%d): %s: (%s)", file, line, func, expression);
	//std::cout << "ASSERT FAILED: " << file << "(" << line << "): " << func << ": (" << expression << ") " << msg;
    //print("ASSERT FAILED: {}({}): {}: ({}) {}", file, line, func, expression, msg);
}
//---