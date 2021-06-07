#if defined(_MSC_VER)
	#pragma comment(lib, "winmm.lib")
#endif

#include <Windows.h>
#include "base_def.h"
#include "base_shared.h"

export module win_sys;

import base_def;



export float sys_win_get_current_time()
{ 
	return scast<float>(timeGetTime())*0.001f; 
}


export void sys_msgbox_error(const char *error, ...)
{
    q_va_vsprintf(text, 1024, error);	
    q_msg_boxw_ok(flib::mb_towstr(text));
}

// Quit app if exit due to unrecoverable error.
export void sys_msgbox_error_quit()
{
    q_msg_boxw_ok(L"Program will now exit");
    // Exit Success is indicated by exit(0) statement which means successful termination of the program,
    // i.e. program has been executed without any error or interrupt
    exit(0);
}