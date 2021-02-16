#include <Windows.h>

#include <memory>

#include <gl/gl.h>

#if defined(_MSC_VER)
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "OpenGL32.lib") 
#endif

using uint = unsigned int;
#define scast	static_cast
#define q_msg_box_ok(msg)   MessageBoxW(NULL, msg, L"Error", 0)

#include <iostream>
#define gout		std::cout	
#define sdflush		std::flush
#define sdf			"\n"

namespace ws
{
class StdConsole
{
public:
	HANDLE hConsole = nullptr;

	StdConsole() {}
	~StdConsole() { deinit(); }
	
	bool init(const char* window_title, int xpos, int ypos, int width, int height)
	{
		if (!AllocConsole()) 
		{ 
			MessageBoxW(nullptr, L"Couldn't create output console.", L"Error", 0); 
			return false; 
		}

		HWND consoleWindow = GetConsoleWindow();
		MoveWindow(consoleWindow, xpos, ypos, width, height, TRUE);
		SetWindowText(consoleWindow, L"Std Console");	

		// The freopen_s function closes the file currently associated with stream and reassigns stream to the file specified by path.
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_RED);
		return true;
	}
		
	void deinit() { FreeConsole(); }
};

class RendererGL2 //: public IRenderer
{
public:
	HGLRC m_hRC = nullptr;
    HDC m_hDC = nullptr;
	HWND m_render_wnidow = nullptr;

	void init(HWND hWnd)
	{
		m_render_wnidow = hWnd;
		m_hDC = GetDC(m_render_wnidow);

		PIXELFORMATDESCRIPTOR pfd = {0};
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;    //32
		pfd.cDepthBits = 16;    //24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;


		int pixel_format = ChoosePixelFormat(m_hDC, &pfd);
		SetPixelFormat(m_hDC, pixel_format, &pfd);

		HGLRC temp_hRC;
		// Are We Able To Get A OpenGL 2.1 Rendering Context?
		temp_hRC = wglCreateContext(m_hDC);
		wglMakeCurrent(m_hDC, temp_hRC);

		// If OpenGL major version <= 2, use the OpenGL 2.1 context
		m_hRC = temp_hRC;
	}

	void deinit()
	{
		if (m_hRC)											
	    {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(m_hRC);
            m_hRC = nullptr;
        }    

        if (m_hDC)
        {
            ReleaseDC(m_render_wnidow, m_hDC);
            m_hDC = nullptr;
        }
	}

	void render(float dt)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);
		glEnd();

		glPopMatrix();    
	}

	void swap_buffers() { SwapBuffers(m_hDC); }

};



constexpr const wchar_t* NW_WINDOW_CLASS_NAME = L"WinSample";

class WinApp
{
public:

	// App data
    HINSTANCE m_app_instance = 0;
    WNDPROC m_wnd_proc = nullptr;
    wchar_t m_app_class_name[64] = {};
    MSG m_msg = {};

    HWND m_active_window = nullptr;
	//HDC m_active_dc = nullptr;
	bool m_is_app_fullscreen = false;

	static constexpr int k_win_app_color_bits = 32;

private:
    bool z_register_class()
	{		
		WNDCLASSEX wcex = {};

		// register window class
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_OWNDC;
		//wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = m_wnd_proc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_app_instance;   
		wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION); 
		wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);	
		//wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcex.hbrBackground = CreateSolidBrush(RGB(255, 165, 0));
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = m_app_class_name; 
		wcex.hIconSm = LoadIconW(nullptr, IDI_APPLICATION); 

		if (!::RegisterClassExW( &wcex ))
		{
			gout << "Could not register class." << sdf;
			return false;
		}

		return true;
	}

public:
	bool init(HINSTANCE app_instance, WNDPROC wnd_proc)
	{
		wcscpy(m_app_class_name, NW_WINDOW_CLASS_NAME);
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

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			gout << "Could not switch to fullscreen." << sdf;
			return false;
		}
		
		return true;
	}

	bool create_window(int posx, int posy, int width, int height, bool is_fullscreen, bool is_borderless)
	{
		if (m_is_app_fullscreen)
		{
			gout << "Another Window is already fullscreen." << sdf;
		}

		if (!is_borderless)
		{
			if (is_fullscreen)
			{            
				if (!set_fullscreen_mode(width, height, k_win_app_color_bits))
				{
					gout << "Could not create fullscreen window with given resolution (" << width << ", " << height << "). Switching to windowed mode." << sdf;
					// Windowed mode selected.
					is_fullscreen = false;		
	
				}
			}
		}

		DWORD		dwExStyle = 0;				// Window Extended Style
		DWORD		dwStyle = 0;				// Window Style


		// Are We Still In Fullscreen Mode?
		// set app fullscreen status
		m_is_app_fullscreen = is_fullscreen;
		if (m_is_app_fullscreen)	
		{
			posx = 0;
			posy = 0;			
			// WS_EX_APPWINDOW forces a top level window down to the taskbar once our window is visible. 
			// WS_EX_TOPMOST makes window on top of other windows.
			dwExStyle = WS_EX_APPWINDOW|WS_EX_TOPMOST;
			is_borderless = true;
		}
		else
		{
			//dwExStyle	= WS_EX_APPWINDOW;								
			// Normal Window with Title Bar
			dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;		
		} 
    
	
		// Set WS_POPUP for borderless window
		if (is_borderless)
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
		RECT window_rect = {0, 0, width, height};
		// Adjust windows rect to account for size of title bar and borders, getting window client area of exactly the requested resolution.
		// The window will be made larger to account for the pixels needed to draw the window border. 
		// In fullscreen mode, this command has no effect.
		AdjustWindowRectEx(&window_rect, dwStyle, false, dwExStyle);
		x = posx + window_rect.left;
		y = posy + window_rect.top;
		w = window_rect.right - window_rect.left;
		h = window_rect.bottom - window_rect.top;	


		HWND handle_wnd = CreateWindowExW(dwExStyle,					
							m_app_class_name,			        
							L"Windows Sample",	 		
							dwStyle,
							x, y, w, h,
							//0, 0, 800, 450,
							nullptr,						// No Parent Window handle				
							nullptr,						// No Menu handle			
							m_app_instance,				    // Program instance handle				
							nullptr);						// Creation parameters, nothing passed to WM_CREATE			

		if (!handle_wnd)
		{							
			gout << "Could not create window." << sdf;
			return false; 
		}
  
		
		ShowWindow(handle_wnd, SW_SHOW);   
		UpdateWindow(handle_wnd); 
		SetForegroundWindow(handle_wnd);						// Slightly Higher Priority
		SetFocus(handle_wnd);									// Sets Keyboard Focus To The Window



		//HDC handle_dc = GetDC(handle_wnd);
		//winapp_class.wnd_list.push_back(winapp_window);

		m_active_window = handle_wnd;
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
		UnregisterClassW(m_app_class_name, m_app_instance);
	}

	int msg_return()
	{
		return scast<int>(m_msg.wParam);
	}

	uint get_msg()
	{
		return m_msg.message;
	}

	bool is_quit_msg()
	{
		if (get_msg() == WM_QUIT) { return true; }
		return false;
	}
};

float sys_win_get_current_time()
{ 
	return scast<float>(timeGetTime())*0.001f; 
}

class AppVars
{
public:
	//HDC		active_dc = nullptr;		
	//HWND		active_window = nullptr;	

	//bool		app_fullscreen = false;
	bool		app_running = true;
	bool		app_active = true;
};

//extern AppVars g_av;
AppVars g_av;

void app_sys_quit() { g_av.app_running = false; }

}

using namespace ws;
//=====================================================
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//======================================
// WinMain
//======================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	StdConsole gconstd;
	gconstd.init("NexWars Std Console", 864, 0, 640, 640);
	gout << "SysConsole Initialized." << sdf;

	WinApp nw_app;

	bool result_ai = nw_app.init(hInstance, MainWndProc);
	if (!result_ai) { q_msg_box_ok(L"WinApp::init Failed"); }
    bool result_cw = nw_app.create_window(10, 50, 800, 450, false, false);
	//bool result_cw = nw_app.create_window(0, 0, 1920, 1080, true, false);
    if (!result_ai) { q_msg_box_ok(L"WinApp::create_window Failed"); }
	
    std::unique_ptr<RendererGL2> renderer;
    renderer = std::make_unique<RendererGL2>();
    renderer->init(nw_app.m_active_window);
 
	
	float delta_time = 0.0f;	
    static float prev_time = sys_win_get_current_time();


    // program main loop
    while (g_av.app_running)
    {
		nw_app.poll_events();

		if (g_av.app_active)				
		{			
            float curr_time  = sys_win_get_current_time(); 
		    delta_time = (curr_time - prev_time);     

            if (nw_app.is_quit_msg())
            {
                //g_av.app_running = false;
                app_sys_quit();
            }	

			renderer->render(delta_time);
            renderer->swap_buffers();

            prev_time = curr_time;            

		}
		else
		{
    		Sleep(1);				
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));	
			continue;
		} 
        
    } // while: app_running


    renderer->deinit();


    nw_app.deinit();

    gconstd.deinit();

    return nw_app.msg_return();
}


//======================================
// Window Procedure
//======================================

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {

    case WM_ACTIVATE:							
	{
		if (!HIWORD(wParam))					
		{
			g_av.app_active = true;
		}
		else
		{
			g_av.app_active = false;
		}

		return 0;		
	}


    case WM_CREATE:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        PostQuitMessage(0);        
        return 0;

    case WM_QUIT:
        PostQuitMessage(0);        
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
		case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;								


    default: break;
    } 
    
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
