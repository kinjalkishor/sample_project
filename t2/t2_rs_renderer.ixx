#include <wtypes.h>

#include "t2_rs_renderer.h"

export module t2_rs_renderer;

import base_def;


  


namespace t2
{

export class IRenderer
{
public:
	virtual fresult<bool> init(HWND hWnd) = 0;
	virtual void deinit() = 0;

	virtual bool setup() = 0;
	virtual void render(float dt) = 0;
	virtual void cleanup() = 0;

    virtual void swap_buffers() = 0;

    //virtual void on_resize() = 0;

	virtual void clear(bool clear_color, const gm::colorf& color, bool clear_depth, float depth_val, bool clear_stencil, int stencil_val) = 0;

};

}




	//virtual void clear_render_target_view(const gm::colorf& color) = 0;
	//virtual void clear_depth_stencil_view(bool clear_depth, float depth_val, bool clear_stencil, int stencil_val) = 0;

	//// <fixed>
	//virtual void begin_scene() {}
	//virtual void end_scene() {}

	////virtual void load_shaders() = 0;

	////------------------------------
	//virtual void set_render_state() {}
	//virtual void load_vertices(float* vertices, intsz num_vertices) {}
	//virtual void set_shaders() {}
	//virtual void draw() = 0;