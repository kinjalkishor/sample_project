//#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
#include <wtypes.h>
//#include <windef.h>
//#include <winbase.h>

#include "base_def.h"
#include "base_debug.h"

//=============================
// Utility functions
//=============================
#define Q_GET_X_LPARAM(lp)                        (scast<int>(scast<int16>(LOWORD(lp))))
#define Q_GET_Y_LPARAM(lp)                        (scast<int>(scast<int16>(HIWORD(lp))))


export module win_app;

import base_def;




//#define	Q_WINDOW_STYLE	(WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE)
constexpr const char* NW_WINDOW_CLASS_NAME = "NexWarsApp";

class WindowData
{
public:
    HWND handle_wnd = nullptr;
    //HDC handle_dc = nullptr;
    int posx = 0;
	int posy = 0;
	int width = 800;
	int height = 600;
    bool is_fullscreen = false;
    bool is_borderless = false;
    char title[128];
    //std::string title;
};

export class WinApp
{
public:

	// App data
    HINSTANCE m_app_instance = 0;
    WNDPROC m_wnd_proc = nullptr;
    char m_app_class_name[64] = {};
    MSG m_msg = {};

    HWND m_active_window = nullptr;
	//HDC m_active_dc = nullptr;
	bool m_is_app_fullscreen = false;

	//bool m_hide_mouse_pointer = false;
	uint m_win_bg_color = RGB(25, 25, 112);
	//uint m_active_wnd_bg_color = gm::to_xbgr(1.0f, 0.5f, 0.0f, 0.0f);	//orange
	//uint m_active_wnd_bg_color = gm::color_to_xbgr(cc::Black);
    //uint m_active_wnd_bg_color = RGB(255,165,0);
    
    // Windows 8 onwards only supports 32 bit color.
    static constexpr int k_color_bits = 32;

private:
	fresult<bool> z_register_class()
	{
		// register window class
		WNDCLASSEX wcex = {};		
		wcex.cbSize = sizeof(wcex);
		// CS_OWNDC Allocates a unique device context for each window in the class
		// Creates a private DC for the Window. Meaning the DC is not shared across applications.
		// CS_CLASSDC Allocates one device context to be shared by all windows in the class
		// CS_HREDRAW | CS_VREDRAW force the Window to redraw whenever it is resized
		// 0 or nullptr for nothing.	
		wcex.style = CS_OWNDC;
		//wcex.style = CS_HREDRAW | CS_VREDRAW;
		//wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw when resized, And Own DC For Window
		// wnd_proc is the procedure that watches for messages in our program.
		wcex.lpfnWndProc = m_wnd_proc;
		// No Extra Window Data
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		// Grab An Instance For Our Window
		wcex.hInstance = m_app_instance;   
		wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION); 
		// Load The Arrow Pointer
		wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);	
		//wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		//wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		//wcex.hbrBackground = CreateSolidBrush(RGB(255, 165, 0));
		wcex.hbrBackground = CreateSolidBrush(m_win_bg_color);
		// No menu
		wcex.lpszMenuName = nullptr;
		// Window class name should be the same name when creating the window of this class, which will have same wnd_proc
		// A window can be created from this template (class public name).
		wcex.lpszClassName = flib::mb_towstr(m_app_class_name); 
		wcex.hIconSm = LoadIconW(nullptr, IDI_APPLICATION); 

		// register window class
		if (!::RegisterClassExW( &wcex ))
		{
			//q_debug("Cannot Register WinApi Class.\n");
			return fresult(false, q_finfo("Cannot Register WinApi Class.\n"));
		}

		return fresult(true);		
	}

	fresult<bool> z_create_window_internal(WindowData& win_data)
	{
		if (m_is_app_fullscreen)
		{
			win_data.is_fullscreen = false;
			q_debug("Another Window is already fullscreen.\n");
		}

		// Set fullscreen mode before you create your window
		// Attempt Fullscreen Mode if window is not borderless		
		if (!win_data.is_borderless)
		{
			if (win_data.is_fullscreen)
			{            
				if (!set_fullscreen_mode(win_data.width, win_data.height, k_color_bits))
				{
					// Try again with desktop dimensions
					//q_debug("Window: %s, Could not create fullscreen window with given resolution (%d, %d). Using desktop resolution.\n", win_data.title.c_str(), win_data.width, win_data.height);
					//win_data.width = GetSystemMetrics(SM_CXSCREEN);
					//win_data.height = GetSystemMetrics(SM_CYSCREEN);
					//
					//if (!set_fullscreen_mode(win_data.width, win_data.height, k_win_app_color_bits)))
					//{
						// If Mode fails offer two options, quit or use Windowed Mode.
						//if (Q_WIN_YES_NO_MB(TEXT("The requested Fullscreen Mode is not supported. Use Windowed Mode instead?"), IDYES))
						//{
					//q_debug("Could not create fullscreen window with given resolution ({}, {})). Switching to windowed mode.\n", win_data.width, win_data.height);
					q_debug("Could not create fullscreen window with given resolution(%d, %d). Switching to windowed mode.\n", win_data.width, win_data.height);
							// Windowed mode selected.
							win_data.is_fullscreen = false;		
					//}
					//else
					//{
					//	winapp_window.fullscreen = false;
					//	// Pop up a Message Box letting user know the program is closing.
					//	q_debug("Could not Create Window.\n");
					//	return false;									// Return false, exit window if false
					//}
				}
			}
		}

		// dwExStyle and dwStyle will store the Extended and normal Window Style Information. I use variables to store 
		// the styles so that I can change the styles depending on what type of window I need to create 
		// (A popup window for fullscreen or a window with a border for windowed mode)
		DWORD dwExStyle = 0;			// Window Extended Style
		DWORD dwStyle = 0;				// Window Style


		// Are We Still In Fullscreen Mode?  Set app fullscreen status
		m_is_app_fullscreen = win_data.is_fullscreen;
		if (m_is_app_fullscreen)	
		{
			win_data.posx = 0;
			win_data.posy = 0;			
			// WS_EX_APPWINDOW forces a top level window down to the taskbar once our window is visible. 
			// WS_EX_TOPMOST makes window on top of other windows.
			dwExStyle = WS_EX_APPWINDOW|WS_EX_TOPMOST;
			win_data.is_borderless = true;
		}
		else
		{
			//dwExStyle	= WS_EX_APPWINDOW;								
			// Normal Window with Title Bar
			dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;		
		} 
    
	
		// Set WS_POPUP for borderless window
		if (win_data.is_borderless)
		{
			// WS_POPUP window has no border around it, making it perfect for fullscreen mode.
			// Windows Style, WS_VISIBLE will create a visible window, or use ShowWindow later
			dwStyle = WS_POPUP|WS_VISIBLE;							
		}
		else
		{
			// WS_EX_WINDOWEDGE gives the window a more 3D look. 			
			// WS_OVERLAPPEDWINDOW creates a window with a title bar, sizing border, window menu, and minimize / maximize buttons.
			dwStyle = WS_OVERLAPPEDWINDOW|WS_VISIBLE;				
		}

		// WS_CLIPSIBLINGS and WS_CLIPCHILDREN are both REQUIRED for OpenGL to work properly. 
		// These styles prevent other windows from drawing over or into our OpenGL Window.
		dwStyle = dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
    

		int x, y, w, h;
		// Grab the upper left, and lower right values of a rectangle. We'll use these values to adjust our window so that the area we draw 
		// on is the exact resolution we want. Normally if we create a 640x480 window, the borders of the window take up some of our resolution.
		// RECT: left, top, right, bottom
		RECT window_rect = {0, 0, win_data.width, win_data.height};
		// Adjust windows rect to account for size of title bar and borders, getting window client area of exactly the requested resolution.
		// The window will be made larger to account for the pixels needed to draw the window border. 
		// In fullscreen mode, this command has no effect.
		AdjustWindowRectEx(&window_rect, dwStyle, false, dwExStyle);
		x = win_data.posx + window_rect.left;
		y = win_data.posy + window_rect.top;
		w = window_rect.right - window_rect.left;
		h = window_rect.bottom - window_rect.top;	

	#if 1
		win_data.handle_wnd = CreateWindowExW(dwExStyle,					
							flib::mb_towstr(m_app_class_name),			        
							flib::mb_towstr(win_data.title),	 		
							dwStyle,
							x, y, w, h,
							//0, 0, 800, 450,
							nullptr,						// No Parent Window handle				
							nullptr,						// No Menu handle			
							m_app_instance,				    // Program instance handle				
							nullptr);						// Creation parameters, nothing passed to WM_CREATE		

	#else

		win_data.handle_wnd = CreateWindowExW(WS_EX_APPWINDOW|WS_EX_WINDOWEDGE,
							flib::mb_towstr(m_app_class_name),
							L"Windows Sample",
							WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
							x, y, w, h,
							nullptr, nullptr, m_app_instance, nullptr);
	#endif


		if (!win_data.handle_wnd)
		{							
			q_debug("Cannot Create Window.\n");
			return fresult(false, q_finfo("Cannot Create Window.\n"));
		}
  
		
		ShowWindow(win_data.handle_wnd, SW_SHOW);   
		UpdateWindow(win_data.handle_wnd); 
		SetForegroundWindow(win_data.handle_wnd);						// Slightly Higher Priority
		SetFocus(win_data.handle_wnd);									// Sets Keyboard Focus To The Window

		//win_data.handle_dc = GetDC(win_data.handle_wnd);
		//winapp_class.wnd_list.push_back(winapp_window);

		// Set to main active window if there is no current active_window
		//if (!m_active_window) { 
		//	m_active_window = win_data.handle_wnd; 
		//	m_active_dc = win_data.handle_dc; 
		//}

		return fresult(true);			
	}

	void z_get_window_size(HWND handle_wnd, int& window_width, int& window_height)
	{
		RECT window_rect;
		GetWindowRect(handle_wnd, &window_rect);
		window_width	= window_rect.right - window_rect.left;
		window_height	= window_rect.bottom - window_rect.top;
	}

public:

	fresult<bool> init(HINSTANCE app_instance, WNDPROC wnd_proc)
	{
		flib::strlcpy(m_app_class_name, NW_WINDOW_CLASS_NAME, 64);
		// Can get app_instance, but take as function parameter for passing nullptr for 
		// console programs having main which creates WinApi windows
		//HINSTANCE app_instance = GetModuleHandle(nullptr); 
		m_app_instance = app_instance;
		m_wnd_proc = wnd_proc;
		return z_register_class();
	}

	bool set_fullscreen_mode(int width, int height, int color_bits)
	{
		DEVMODE dmScreenSettings = {};								    // Device Mode
		dmScreenSettings.dmSize			= sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				        // Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				        // Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= color_bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results. Note: CDS_FULLSCREEN Gets Rid Of Start Bar.
		// Use the parameter CDS_FULLSCREEN when switching modes, because it's supposed to remove the start bar at the bottom of the screen, 
		// plus it doesn't move or resize the windows on your desktop when you switch to fullscreen mode and back.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			q_debug("Could not switch to fullscreen.\n");
			return false;
		}
		
		return true;
	}

	fresult<bool> create_window(const char* window_title, int posx, int posy, int width, int height, bool is_fullscreen, bool is_borderless)
	{
		WindowData win_data;
		win_data.posx = posx;
		win_data.posy = posy;
		win_data.width = width;
		win_data.height = height;		
		win_data.is_fullscreen = is_fullscreen;
		win_data.is_borderless = is_borderless;
		//wcscpy(win_data.title, flib::mb_towstr(window_title));   
		//win_data.title.reserve(128);
		//win_data.title = window_title;
		flib::strlcpy(win_data.title, window_title, 128);

		auto result_cwi = z_create_window_internal(win_data);
		// Set to main active window if there is no current active_window
		if (!m_active_window) 
		{ 
			m_active_window = win_data.handle_wnd; 
			//m_active_dc = win_data.handle_dc;
		}

		return result_cwi;	
	}


	// Polling messages when poll_events(msg) returns true
	// Checks the message queue to see if any windows messages (window is closing, window is resizing, key pressed, etc)
	// are waiting and if there are, the messages are dispatched to our message handler.
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
	#if 0
		if (!main_app.wnd_list.empty())
		{
			for (auto i: main_app.wnd_list)
			{
				if (i.hWnd)			
				{
					// Are We Able To Destroy The Window?
					if (!DestroyWindow(i.hWnd))
					{
						q_debug("Could Not Release hWnd of Window: %s\n", i.title);
					}
					else
					{
						i.hWnd = nullptr;				
					}
				}

				main_app.wnd_list.pop_back();
			}
		}
	#endif

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

	//---------------------	
	void show_mouse_pointer() { ShowCursor(true); }
	void hide_mouse_pointer() { ShowCursor(false); }

	void move_window(HWND handle_wnd, int posx, int posy, int width, int height)
	{
		int window_width, window_height;
		z_get_window_size(handle_wnd, window_width, window_height);

		//print("{}, {}\n", window_width, window_height);

		// Calculate new adjusted width and height
		RECT client_rect;
		GetClientRect(handle_wnd, &client_rect);
		//print("{}, {}\n", client_rect.right, client_rect.bottom);

		window_width	= width + (window_width - client_rect.right);
		window_height	= height + (window_height - client_rect.bottom);

		//print("{}, {}\n", window_width, window_height);


		MoveWindow(handle_wnd, posx, posy, window_width, window_height, TRUE);
	}

	void get_window_client_size(HWND handle_wnd, int& window_width, int& window_height)
	{
		RECT client_rect;
		GetClientRect(handle_wnd, &client_rect);
		window_width	= client_rect.right - client_rect.left;
		window_height	= client_rect.bottom - client_rect.top;
	}

};


#if 0
HDC get_device_context()
{        
    return m_active_dc;
}


HWND create_child_window(HWND parent_window, int posx, int posy, int width, int height)
{
    RECT rcWnd = {0};
    GetClientRect(parent_window, &rcWnd);

    return CreateWindowExW(WS_EX_CLIENTEDGE, L"static", 
                            nullptr, WS_CHILD|SS_BLACKRECT|WS_VISIBLE,
                            posx, posy, width, height, 
                            parent_window, nullptr, m_app_instance, nullptr);
}

#if 0
void create_child_window_multiple()
{
    HWND hWnd3D[4] = {0};
    RECT rcWnd;
    int x = 0, y = 0; 

   // build for child windows
   GetClientRect(m_active_window, &rcWnd);

    for (int i=0; i<4; i++) 
    {
        if ( (i==0) || (i==2) ) 
        { 
            x = 10; 
        }
        else 
        {
            x = rcWnd.right/2 + 10;
        }

        if ( (i==0) || (i==1) ) 
        {
            y = 10;
        }
        else 
        {
            y = rcWnd.bottom/2 + 10;
        }

        hWnd3D[i] = CreateWindowExW(WS_EX_CLIENTEDGE, TEXT("static"), 
                            nullptr, WS_CHILD | SS_BLACKRECT | WS_VISIBLE,
                            x, y, rcWnd.right/2-20, rcWnd.bottom/2-20, 
                            m_active_window, nullptr, m_app_instance, nullptr);
    }

    // init render device
    //return g_pDevice->Init(g_hWnd, hWnd3D, 4, 16, 0, false);   
}
#endif


void show_window(HWND handle_wnd)
{
	ShowWindow(handle_wnd, SW_RESTORE);
}

void hide_window(HWND handle_wnd)
{
	ShowWindow(handle_wnd, SW_HIDE);
}


void set_window_title(HWND handle_wnd, const char* window_title)
{
	SetWindowText(handle_wnd, flib::mb_towstr(window_title));
}


void set_window_pos(HWND handle_wnd, int posx, int posy)
{
	int window_width, window_height;
	get_window_size(handle_wnd, window_width, window_height);

	//print("{}, {}\n", window_width, window_height);

	MoveWindow(handle_wnd, posx, posy, window_width, window_height, TRUE);
}


void set_window_centered(HWND handle_wnd)
{
	int window_width, window_height;
	get_window_size(handle_wnd, window_width, window_height);

	// calculate centred posx and posy
	int screen_width, screen_height;
	int centre_posx, centre_posy;
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	centre_posx = (screen_width - window_width) / 2;
	centre_posy = (screen_height - window_height) / 2;

	//print("{}, {}\n", window_width, window_height);

	MoveWindow(handle_wnd, centre_posx, centre_posy, window_width, window_height, TRUE);
}

void create_render_context(int major_version, int minor_version)
{		
	//if (m_create_render_context == true)
	//{
		//gl_ext_loader_lib_init();
		// Enable GLEW
		//if(!gl_ext_loader_lib_init())
		//{
		//	return false;
		//}
	//}
}

void switch_to_desktop()
{
	if (g_av.app_fullscreen)							// Are We In Fullscreen Mode?
	{
		// ChangeDisplaySettings(NULL,0) to return us to our original desktop. Passing NULL as the first parameter and 0 as 
		// the second parameter forces Windows to use the values currently stored in the Windows registry (the default resolution,
		// bit depth, frequency, etc) effectively restoring our original desktop. 
		// After we've switched back to the desktop we make the cursor visible again.
		ChangeDisplaySettings(nullptr,0);				// If So Switch Back To The Desktop
		//ShowCursor(true);								// Show Mouse Pointer

		fullscreen = false;

		// Set global fullscreen app status
		g_av.app_fullscreen = fullscreen;

	}
}

#endif