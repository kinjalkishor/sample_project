#pragma once

#include "base_def.h"
#include <Windows.h>

class StdConsole
{
private:
	const char* console_title = "Std Console";

	HANDLE hConsole = nullptr;	

private:
	//void print_string_color(const char* message, uint con_color);

public:
	StdConsole() {}
	~StdConsole() { deinit(); }

	bool init(const char* window_title, int xpos, int ypos, int width, int height);
	void deinit();

	//void print_string(const char* message);
	//void print_debug_string(const char* message);
	//void print_error_string(const char* message);		
};

//extern StdConsole gconstd;

//------------------------------------------
// <iostream> is required for std::cout
#include <iostream>
#include <iomanip>
#include <sstream>




#define gprintf		std::printf
#define gout		std::cout	
//#define gerr		std::cerr	


#define sdflush		std::flush
//#define sdf		std::endl
//#define sdf		"\n"

// newline
inline std::ostream& sdf(std::ostream& os)  { return os << '\n'; }


#define qcs			", "
#define qtb 		"\t"


#define q_print_new_line()	gprintf("\n")
#define q_print_sep_line()	gprintf("\n--------------------------------\n")



//---------------------------------------------------
// Error Logging with source code location
// __FUNCTION__ gives function name with class, __func__ gives only function name.
// #x prints quoted string, x prints without quotes 

//#define debug_log(msg) \
//{ \
//    gout << "ERROR - \nFile: " << __FILE__ << "\nLine: " << __LINE__ << "\nFunc: " << __FUNCTION__ << "\nError: " << #msg << sdf; \
//}
//#define q_debug_log(msg)		gout << "ERROR: " << __FUNCTION__ << ": " << #msg << sdf 


void debug_log(const char* label, const char* file, int line, const char* func, const char* msg);
#define q_debugf(msg)		debug_log("", __FILE__, __LINE__, __FUNCTION__, #msg)
#define q_err_msg(msg)		debug_log("ERROR: ", __FILE__, __LINE__, __FUNCTION__, msg)

// var should be fresult
#define q_result_check(var) \
if (var.failed()) { q_err_msg(var.msg); }



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


// Run time assert checking. Can disable for final release version.
void check_assert(const char *file, int line, const char* func, const char *expression, const char *msg);

#define Q_CFG_CHECK_ASSERTS

#if defined(Q_CFG_CHECK_ASSERTS)
#define q_assert2(expression, msg)	if (!(expression)) check_assert(__FILE__, __LINE__, __FUNCTION__, #expression, msg)
#else
#define q_assert2(expression, msg)
#endif
#define q_assert(expression)	q_assert2(expression, "")
