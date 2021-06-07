#include <Windows.h>

#include "base_def.h"
#include "base_iostream.h"
#include "base_debug.h"
#include "base_gmath_wp.h"

import base_def;
import base_console;

import win_app;
import win_sys;



// Lua include
#if defined(_MSC_VER)
//#pragma comment(lib, "../../dep/lib/lualib.lib")
#endif
// ../../dep/lua/src
//#include "lua.hpp"
//#include "../../dep/lua/src/lua.hpp"
// ../../dep/sol2/include/
//#include "sol/sol.hpp"
// forward.hpp also available
//#include "sol/forward.hpp"

import t2_rs_renderer;
//declare pointers then no need to include these headers if using IRender
import t2_rs_gl4_renderer;
import t2_rs_d3d11_renderer;
//#include"t2/t2_rs_gl2_renderer.h"
//#include"t2/t2_rs_d3d9_renderer.h"



//#include <memory> //unique_ptr

using namespace t2;

//---
class AppVars
{
public:
    //HDC		active_dc = nullptr;		
	//HWND		active_window = nullptr;	
	//bool		app_fullscreen = false;

	bool		app_running = true;
	bool		app_active = true;
    void sys_quit() { app_running = false; }
};
//extern AppVars g_av;
AppVars g_av;

extern gm::vidinfo g_ws;



using namespace t2;
//=====================================================
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//-----------------------------------




//======================================
// WinMain
//======================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	StdConsole gconstd;
	gconstd.create_window("NexWars Std Console", 864, 0, 640, 640);
	print("SysConsole Initialized.\n");
    print("Nex t2.\n");

	//----------------------------------------------------------------
#if 1   
    q_print_sep_line();
    //----------------------------------------------------------------   






    //----------------------------------------------------------------
#endif
    //----------------------------------------------------------------
    q_print_sep_line();



    //-------------------
	WinApp nw_app;

    static char window_title[] = "Nex Wars";  

     // get from config file or cvars
    int posx = 10;
    int posy = 50;
    int width = 800;
    int height = 450;
    int fs_width = 1280;
    int fs_height = 720;
    // 16:9: 1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080, 2560×1440 and 3840×2160.
    bool is_fullscreen = 0;
    bool is_borderless = 0;
    if (is_fullscreen) { width = fs_width; height = fs_height; }

    //-------------------
	auto result_ai = nw_app.init(hInstance, MainWndProc);
    q_result_check(result_ai); 
    if (result_ai.failed()) { q_error("%s", result_ai.msg); sys_msgbox_error_quit(); }
    auto result_cw = nw_app.create_window(window_title, posx, posy, width, height, is_fullscreen, is_borderless);
    //auto result_cw = nw_app.create_window("Nex Wars", 10, 50, 800, 450, false, false);
    //auto result_cw = nw_app.create_window("Nex Wars", 0, 0, 1920, 1080, true, false);
    if (result_cw.failed()) { q_error("%s", result_cw.msg); sys_msgbox_error_quit(); }

    // Set global vidinfo
    g_ws.fullscreen = nw_app.m_is_app_fullscreen;
    nw_app.get_window_client_size(nw_app.get_active_window(), g_ws.width, g_ws.height);

    //std::unique_ptr<IRenderer> renderer;
#if 0
    std::unique_ptr<RendererGL4> renderer = std::make_unique<RendererGL4>();    
#else
    std::unique_ptr<RendererD3D11> renderer = std::make_unique<RendererD3D11>();
#endif

    //std::unique_ptr<RendererGL2> renderer = std::make_unique<RendererGL2>();
    //std::unique_ptr<RendererD3D9> renderer = std::make_unique<RendererD3D9>();

    auto result_ri = renderer->init(nw_app.get_active_window());
    q_result_check(result_ri); 
    renderer->setup();

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
                g_av.sys_quit();
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

    renderer->cleanup();
    renderer->deinit();

    nw_app.deinit();

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
		if (!HIWORD(wParam))	{ g_av.app_active = true; }
		else					{ g_av.app_active = false; }
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


#if 0
    case WM_SYSKEYDOWN:	
    case WM_KEYDOWN:        						
	{
		g_keys[wParam] = true;		
        ////app_key_event();
		break;								
	}

	case WM_SYSKEYUP:
    case WM_KEYUP:        							
	{
		g_keys[wParam] = false;					
		break;								
	}
#endif

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