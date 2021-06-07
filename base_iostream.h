#include <iostream>
#include <format>


namespace iofmt 
{

// iostream, format functions have iostream multiple defined errors in modules
template <class... _Types>
_NODISCARD void print(const std::string_view _Fmt, const _Types&... _Args) {
    std::cout << std::vformat(_Fmt, std::make_format_args(_Args...));
	//std::printf("%s", std::vformat(_Fmt, std::make_format_args(_Args...)).c_str());
}

}

using namespace iofmt;



//------------------------------------------
inline void q_print_sep_line()	{ std::printf("\n--------------------------------\n"); }


#if 0
// <iostream> is required for std::cout
//#include <iostream>
//#include <iomanip>
//#include <sstream>

//#define gprintf		std::printf
//#define gout		std::cout	
//#define gerr		std::cerr	


//#define sdflush		std::flush
//#define sdf		std::endl
//#define sdf		"\n"

// newline
//inline std::ostream& sdf(std::ostream& os)  { return os << '\n'; }
//#define qcs			", "
//#define qtb 		"\t"

// streams seem slow because by default the iostreams are synchronizing with C FILE output so that intermixed
// cout and printfs are output correctly. Disabling this causes c++'s streams to outperform stdio.
//std::cout.sync_with_stdio(false);    

//inline void writef(const std::string_view fmt_str) { std::cout << fmt_str; }

//---------------------------------------------------

//#define MY_PRINT(format, ...)	std::printf(format "\n", __VA_ARGS__)	//MSVC
//#define MY_PRINT(format, ...)	std::printf(format "\n", ##__VA_ARGS__)	//GNU GCC

// Error Logging with source code location
// __FUNCTION__ gives function name with class, __func__ gives only function name.
// #x prints quoted string, x prints without quotes 

//#define debug_log(msg) \
//{ \
//    gout << "ERROR - \nFile: " << __FILE__ << "\nLine: " << __LINE__ << "\nFunc: " << __FUNCTION__ << "\nError: " << #msg << sdf; \
//}
//#define q_debug_log(msg)		gout << "ERROR: " << __FUNCTION__ << ": " << #msg << sdf 


//---
#if 0
inline void ptr_log_error(const char* file, int line, const char* func, const char* ptr_name)
{ 
	gout << file << " (" << line << "): " << func << ": '" << ptr_name << "' pointer is null." << sdf;
}
#define q_ptr_log(ptr)			ptr_log_error(__FILE__, __LINE__, __FUNCTION__, #ptr)
//#define q_ptr_log(ptr)		gout << __FILE__ << " (" << __LINE__ << "): " << __FUNCTION__ << ": '" << #ptr << "' pointer is null." << sdf

//#define q_check_nullptr(ptr)	{ if(!(ptr)) { gprintf("%s (%d): %s: '%s' pointer is null ", __FILE__, __LINE__, __FUNCTION__, #ptr); } }
#define q_check_nullptr(ptr)						{ if(!(ptr)) { q_ptr_log(ptr); } }
#define q_check_nullptr_func(ptr, func_to_execute)	{ if(!(ptr)) { q_ptr_log(ptr); (func_to_execute); } }

#define q_bool_log(bool_val, msg)				gout << "ERROR: " << __FUNCTION__ << ": " << #bool_val << ": " << msg << sdf
// check if bool_val needs to be printed
//#define q_check_bool(bool_val, msg)				{ if(!(bool_val)) { q_debug_log(msg); } } 
//#define q_check_bool_return(bool_val, msg)		{ if(!(bool_val)) { q_debug_log(msg); return false; } } 	
#define q_check_bool(bool_val, msg)				{ if(!(bool_val)) { q_bool_log(bool_val, msg); } } 
#define q_check_bool_return(bool_val, msg)		{ if(!(bool_val)) { q_bool_log(bool_val, msg); return false; } } 	
#endif

#endif

