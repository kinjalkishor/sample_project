#define WIN32_LEAN_AND_MEAN
#include <wtypes.h>

#include "base_def.h"

export module win_app_basic;

import base_def;


namespace ts
{

export class WinApp
{
public:
    HINSTANCE m_app_instance = 0;
    WNDPROC m_wnd_proc = nullptr;
    char m_app_class_name[64] = {};
    MSG m_msg = {};
    HWND m_active_window = nullptr;
	bool m_is_app_fullscreen = false;
	uint m_win_bg_color = RGB(25, 25, 112);

	bool init(HINSTANCE app_instance, WNDPROC wnd_proc) 
	{		
		strcpy(m_app_class_name, "WIN_SAMPLE_CLASS");
		m_app_instance = app_instance;
		m_wnd_proc = wnd_proc;
		WNDCLASSEX wcex = 
		{
			sizeof(wcex), CS_OWNDC, m_wnd_proc, 0, 0, m_app_instance, 
			LoadIconW(nullptr, IDI_APPLICATION), LoadCursorW(nullptr, IDC_ARROW), 
			CreateSolidBrush(m_win_bg_color), nullptr, flib::mb_towstr(m_app_class_name), 
			LoadIconW(nullptr, IDI_APPLICATION)
		};
		if (!::RegisterClassExW( &wcex )) { return false; }
		return true;
	}

	bool create_window(const char* title, int posx, int posy, int width, int height, bool is_fullscreen, bool is_borderless)
	{
		DWORD dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
		DWORD dwStyle = WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
		int x, y, w, h;
		RECT window_rect = {0, 0, width, height};
		AdjustWindowRectEx(&window_rect, dwStyle, false, dwExStyle);
		x = posx + window_rect.left; 
		y = posy + window_rect.top;
		w = window_rect.right - window_rect.left;
		h = window_rect.bottom - window_rect.top;	

		m_active_window = CreateWindowExW(dwExStyle,
						flib::mb_towstr(m_app_class_name),
						L"Windows Sample", dwStyle,
						x, y, w, h,
						nullptr, nullptr, m_app_instance, nullptr);
		if (!m_active_window) { return false; }
		return true;
	}

	void poll_events()
	{
		if (PeekMessageW(&m_msg, nullptr, 0, 0, PM_REMOVE))	
		{		
			TranslateMessage(&m_msg);				
			DispatchMessageW(&m_msg);				
		}
	}

	void deinit()
	{
		if (DestroyWindow(m_active_window)) { m_active_window = nullptr; }
		UnregisterClassW(flib::mb_towstr(m_app_class_name), m_app_instance);
	}

	int msg_return() { return scast<int>(m_msg.wParam); }

	uint get_msg() { return m_msg.message; }

	bool is_quit_msg()
	{
		if (get_msg() == WM_QUIT) { return true; }
		return false;
	}

	HWND get_active_window() { return m_active_window; }
};

}