#if 1
//=============================
// Load OpenGL extensions
//=============================
#define USE_GLEW 1

// Include win_app.h before render_system.h
#ifdef USE_GLEW
	// Include before GL.h, SDL.h, glfw3.h
	#define GLEW_STATIC
	#include "E:/nex/NexEngine/NexWars/source/dep/glew/include/GL/glew.h"
	#include "E:/nex/NexEngine/NexWars/source/dep/glew/include/GL/wglew.h"

	#pragma comment(lib, "E:/nex/NexEngine/NexWars/source/dep/lib/glew32s.lib")
#endif

//---
#endif

#include "../base_def.h"
#include "../base_iostream.h"
#include "t2_rs_renderer.h"

// GL.h ERROR:  'void' should be preceded by ';'
// include <windows.h> before <gl/gl.h> or <gl/glu.h>. It is needed for some types, such as WINGDIAPI and APIENTRY.
//#include <windows.h>
#include <gl/gl.h>

export module t2_rs_gl4_renderer;

import base_def;
import t2_rs_renderer;




namespace t2
{


#ifdef USE_GLEW
// defined in win_app.cpp
bool gl_ext_loader_lib_init();

// Load OpenGL extensions
inline bool gl_ext_loader_lib_init()
{
//#if USE_GLAD_LIB
//    // glad: load all OpenGL function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        //gprintf("Failed to initialize GLAD in WinMain.\n");
//		return false;
//    }    
//#else
	//GLenum error = glewInit(); // Enable GLEW
	//if (error != GLEW_OK)  { q_debug("Failed to Init GLEW.\n"); } //return false; }

	// Initialize GLEW after you have given OpenGL a context. 
	glewExperimental = GL_TRUE;		// Needed for core profile
	if (glewInit() != GLEW_OK) 
	{
		//gprintf("Failed to initialize GLEW in WinMain.\n");
		return false;
	}
//#endif
	return true;
}
#endif



#if 0
#include "E:/nex/NexEngine/NexWars/source/dep/GL/wglext.h"

#define __ARB_ENABLE true											// Used To Disable ARB Extensions Entirely
// #define EXT_INFO													// Do You Want To See Your Extensions At Start-Up?
//#define MAX_EXTENSION_SPACE 10240									// Characters for Extension-Strings
//#define MAX_EXTENSION_LENGTH 256									// Maximum Of Characters In One Extension-String

#if 0
PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB	= NULL;
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	= NULL;
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB	= NULL;
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB	= NULL;
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB= NULL;	
 isMultitextureSupported() Checks At Run-Time If Multitexturing Is Supported
bool initMultitexture(void) 
 {
	char *extensions;	
	extensions=strdup((char *) glGetString(GL_EXTENSIONS));			// Fetch Extension String
	int len=strlen(extensions);
	for (int i=0; i<len; i++)										// Separate It By Newline Instead Of Blank
		if (extensions[i]==' ') extensions[i]='\n';

#ifdef EXT_INFO
	MessageBox(hWnd,extensions,"supported GL extensions",MB_OK | MB_ICONINFORMATION);
#endif

	if (isInString(extensions,"GL_ARB_multitexture")				// Is Multitexturing Supported?
		&& __ARB_ENABLE												// Override-Flag
		&& isInString(extensions,"GL_EXT_texture_env_combine"))		// Is texture_env_combining Supported?
	{	
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&maxTexelUnits);
		glMultiTexCoord1fARB	= (PFNGLMULTITEXCOORD1FARBPROC)		wglGetProcAddress("glMultiTexCoord1fARB");
		glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord3fARB	= (PFNGLMULTITEXCOORD3FARBPROC)		wglGetProcAddress("glMultiTexCoord3fARB");
		glMultiTexCoord4fARB	= (PFNGLMULTITEXCOORD4FARBPROC)		wglGetProcAddress("glMultiTexCoord4fARB");
		glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC)	wglGetProcAddress("glClientActiveTextureARB");		
#ifdef EXT_INFO
	MessageBox(hWnd,"The GL_ARB_multitexture extension will be used.","feature supported!",MB_OK | MB_ICONINFORMATION);
#endif
		return true;
	}
	useMultitexture=false;											// We Can't Use It If It Isn't Supported!
	return false;
}
#endif

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
#endif


//---
struct gl_api_version
{
	int major = 3;
	int minor = 3;
};
static gl_api_version rs_gl_api_version = {4,6};
//---
uint shaderProgram;
uint VBO, VAO;

//==========================================

// .vert - a vertex shader
// .tesc - a tessellation control shader
// .tese - a tessellation evaluation shader
// .geom - a geometry shader
// .frag - a fragment shader
// .comp - a compute shader
// vs, fs, gs, vsh, fsh, gsh, vshader, fshader, gshader, vert, frag, geom, tesc, tese, comp, glsl
// .vs, .ps, .gs,

// Vertex shader
const char* vertexShaderSource = R"glsl(
	#version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)glsl";


// Fragment shader
const char* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
       FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)glsl";


//uint shaderProgram;
uint vertexShader = 0;
uint fragmentShader = 0;
//uint VBO, VAO;


//---------------------------------------
export class RendererGL4
{
public:
	HGLRC m_hRC = nullptr;
    HDC m_hDC = nullptr;
	HWND m_render_window = nullptr;


	fresult<bool> init(HWND hWnd)
	{
		wglCreateContextAttribsARB	= (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");


		m_render_window = hWnd;
		if (!m_render_window) { return fresult(false, q_finfo("Window Handle passed to init is null.\n")); }	
		m_hDC = GetDC(m_render_window);
		if (!m_hDC) { return fresult(false, q_finfo("Cannot get device context of render window.\n")); }

		// Set Pixel Format for device context of window
		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		// Format Must Support Window, OpenGL, Double Buffering
		pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;		// RGBA Format
		pfd.cColorBits = 24;    //32		// Color Depth
		pfd.cDepthBits = 16;    //24		// Z-Buffer (Depth Buffer)
		pfd.cStencilBits = 8;				// Stencil buffer
		pfd.iLayerType = PFD_MAIN_PLANE;	// Main Drawing Layer

		// Did Windows Find A Matching Pixel Format?
		int pixel_format = ChoosePixelFormat(m_hDC, &pfd);
		if (!pixel_format) { return fresult(false, q_finfo("ChoosePixelFormat failed.\n")); }		
		if (!SetPixelFormat(m_hDC, pixel_format, &pfd)) { return fresult(false, q_finfo("SetPixelFormat failed.\n")); }

		HGLRC temp_hRC;
		// Are We Able To Get A OpenGL 2.1 Rendering Context?
		temp_hRC = wglCreateContext(m_hDC);
		if (!temp_hRC) { return fresult(false, q_finfo("OpenGL2.1, wglCreateContext failed\n")); }
		// Make the OpenGL 2.1 context current and active
		if (!wglMakeCurrent(m_hDC, temp_hRC)) { return fresult(false, q_finfo("OpenGL 2.1 Activate Rendering Context, wglMakeCurrent failed\n")); }

		// If OpenGL major version <= 2, use the OpenGL 2.1 context
		//m_hRC = temp_hRC;

		//==============================================
		//OpenGL 3.3 and above

		if ((rs_gl_api_version.major < 3) || (rs_gl_api_version.major == 3 && rs_gl_api_version.minor < 3))
		{ 
			return fresult(false, q_finfo("OpenGL below Version 3.3 not Suported\n"));
		}
		else
		{
		#if defined(USE_GLEW)
			gl_ext_loader_lib_init();
		#endif

			// Try to get a OpenGL 3.3 Rendering Context. Forward compatible does not have deprecated functions.
			int attributes[] = 
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, rs_gl_api_version.major, 
				WGL_CONTEXT_MINOR_VERSION_ARB, rs_gl_api_version.minor, 
				WGL_CONTEXT_FLAGS_ARB, 
				WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,		// Set our OpenGL context to be forward compatible
				0
			};

			// CORE_PROFILE
			// compatible with OpenGL 2.1
			//int attributes[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0, 0 };

			if (wglewIsSupported("WGL_ARB_create_context")) 
			{ 
				// If OpenGL 3.3 context creation extension is available Create a OpenGL 3.3 context based on the given attributes
				m_hRC = wglCreateContextAttribsARB(m_hDC, nullptr, attributes);		
				// Remove the temporary context from being active
				wglMakeCurrent(nullptr, nullptr);											
				// Delete the temporary OpenGL 2.1 context
				wglDeleteContext(temp_hRC);											
				// Make our OpenGL 3.3 context current
				wglMakeCurrent(m_hDC, m_hRC);										
			}

		} //OpenGL 3.3

		// Output which version of OpenGL we are using
		//print_opengl_version();

		//on_resize();

		return fresult(true);
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
			ReleaseDC(m_render_window, m_hDC);	
			m_hDC = nullptr;
		}
	}

	bool setup()
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	#if 1
		// build and compile our shader program
		// ------------------------------------
		// vertex shader
		//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			print("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}\n", infoLog);
		}

		// fragment shader
		//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			print("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}\n", infoLog);
		}

		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			print("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog);
		}
	#endif

	#if 0
		glt::gl_compile_shader_string(vertexShader, vertexShaderSource);
		glt::gl_compile_shader_string(fragmentShader, fragmentShaderSource);
	#else

		//glt::gl_compile_shader_file(vertexShader, TUT_LOGL_SH_PATH("c1_1_hello_triangle.vs"));
		//glt::gl_compile_shader_file(fragmentShader, TUT_LOGL_SH_PATH("c1_1_hello_triangle.fs"));
	#endif

		//glt::gl_link_shaders_vs_ps(shaderProgram, vertexShader, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// only this line can directly load shaders in shaderProgram
		//glt::gl_load_shaders_vs_ps(shaderProgram, TUT_LOGL_SH_PATH("c1_1_hello_triangle.vs"), TUT_LOGL_SH_PATH("c1_1_hello_triangle.fs")); 

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		}; 



		//unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

	#if 1
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0); 
	#else

		glt::gl_load_buffer_vbo(VAO, VBO, vertices, sizeof(vertices));
		int elem_size_arr[1] = {3};
		glt::gl_generate_vbo_arr(elem_size_arr, ARRAY_SIZE(elem_size_arr));
	#endif


		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		return true;
	}

	void render(float dt)
	{
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Set shaders
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// Draw
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time 
	}

	void cleanup()
	{
		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}   


    void swap_buffers() { SwapBuffers(m_hDC); }

    //void on_resize();

	void clear(bool clear_color, const gm::colorf& color, bool clear_depth, float depth_val, bool clear_stencil, int stencil_val)
	{
		// gl2
		//uint clear_flag = 0;
		//if (clear_color) { clear_flag = clear_flag|GL_COLOR_BUFFER_BIT; glClearColor(color[0], color[1], color[2], color[3]);}
		//if (clear_depth) { clear_flag = clear_flag|GL_DEPTH_BUFFER_BIT; glClearDepth(depth_val); }
		//if (clear_stencil) { clear_flag = clear_flag|GL_STENCIL_BUFFER_BIT; glClearStencil(stencil_val); }    
		//glClear(clear_flag);

		if (clear_color) { glClearBufferfv(GL_COLOR, 0, color.data()); }
		if (clear_depth) { glClearBufferfv(GL_DEPTH, 0, &depth_val); }
		if (clear_stencil) { glClearBufferiv(GL_STENCIL, 0, &stencil_val); }
	}

};

}