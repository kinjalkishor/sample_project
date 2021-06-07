#include <wtypes.h>
#include <cstdio>
#include "base_def.h"

export module base_console;

import base_def;


namespace StdConsole_local
{
const uint color_blue = FOREGROUND_BLUE;
const uint color_green = FOREGROUND_GREEN;
const uint color_red = FOREGROUND_RED;
//cyan is green+blue, magenta is red+blue, and yellow is red+green
const uint color_cyan = FOREGROUND_BLUE|FOREGROUND_GREEN;
const uint color_magenta = FOREGROUND_BLUE|FOREGROUND_RED;
const uint color_yellow = FOREGROUND_GREEN|FOREGROUND_RED;	
// default is white color
const uint color_default = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;

static HANDLE hConsole = nullptr;	
}

export class StdConsole
{
private:
	const char* console_title = "Std Console";	

private:
	//void print_string_color(const char* message, uint con_color);

public:
	StdConsole() {}
	~StdConsole()
	{
		FreeConsole();
		//check if(hConsole)
	}

	bool create_window(const char* window_title, int xpos, int ypos, int width, int height)
	{
		console_title = window_title;

		if (!AllocConsole())
		{
			MessageBoxW(nullptr, L"Couldn't create output console", L"Error", 0);
			return false; 
		}

		HWND consoleWindow = GetConsoleWindow();
		//SetWindowPos(consoleWindow, 0, 864, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);	
		MoveWindow(consoleWindow, xpos, ypos, width, height, TRUE);
		//SetActiveWindow(g_av.active_window);
		//SetFocus(g_av.active_window);
		//SetWindowText(consoleWindow, L"Console Window");
		SetWindowText(consoleWindow, flib::mb_towstr(console_title));
	

		// The freopen_s function closes the file currently associated with stream and reassigns stream to the file specified by path.
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		//std::printf("Debugging Window:\n");

		StdConsole_local::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(StdConsole_local::hConsole, StdConsole_local::color_yellow);

		//set_console_colors(bg_color);

		return true;
	}

	//void print_string(const char* message);
	//void print_debug_string(const char* message);
	//void print_error_string(const char* message);		
};




#if 0
void StdConsole::print_string_color(const char* message, uint con_color)
{
	SetConsoleTextAttribute(hConsole, con_color);

	std::printf(message);

	// set default white foreground and black background
	//SetConsoleTextAttribute(hConsole, 15);
	SetConsoleTextAttribute(hConsole, StdConsole_local::color_default);
}

void StdConsole::print_string(const char* message)
{
	//std::printf(message);
	print_string_color(message, StdConsole_local::color_yellow);
}

void StdConsole::print_debug_string(const char* message)
{		
	print_string_color(message, StdConsole_local::color_green);
}

void StdConsole::print_error_string(const char* message)
{
	print_string_color(message, StdConsole_local::color_magenta);
}

void set_console_colors(WORD attribs)
{
	//HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hConsole, &cbi);
	cbi.wAttributes = attribs;
	SetConsoleScreenBufferInfoEx(hConsole, &cbi);
}
#endif