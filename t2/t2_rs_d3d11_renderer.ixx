//#include <Windows.h>

#include <d3d11.h>
//#include <d3d11_3.h>
#include <d3d11_4.h>


// for compiling shader files, D3DCompileFromFile
#include <D3Dcompiler.h>
//#include <D3Dcommon.h>

#if defined(_MSC_VER)
    #pragma comment(lib, "d3d11.lib")
    #pragma comment(lib, "d3dcompiler.lib")
#endif

#include "../base_def.h"
#include "../base_shared.h"
#include "t2_rs_renderer.h"

#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p) = nullptr; } }


export module t2_rs_d3d11_renderer;

import base_def;
import t2_rs_renderer;




struct rcfg
{
	int msaa_samples = 4;
	bool msaa_enable = true;
} g_rcfg;

//#define D3D11_NEW
//Directional, Sky, Point, Spot, and Rect Lights

template<class Tderived, class Tbase>
HRESULT com_uuid_cast(Tderived& derived_class, const Tbase& base_class)
{
	return base_class->QueryInterface(__uuidof(Tderived), rcast<void**>(&derived_class));
}

export namespace t2
{


// Microsoft D3D11 samples
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const wchar_t* szFileName, const char* szEntryPoint, const char* szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    if ( !szFileName || !szEntryPoint || !szShaderModel || !ppBlobOut )
    {
       return E_INVALIDARG;
    }

    *ppBlobOut = nullptr;

    UINT dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    const D3D_SHADER_MACRO defines[] = 
    {
        "EXAMPLE_DEFINE", "1",
        NULL, NULL
    };

    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    //hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, 
    //    dwShaderFlags, 0, &shaderBlob, &errorBlob);
    hr = D3DCompileFromFile( szFileName, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, &shaderBlob, &errorBlob );

    if ( FAILED(hr) )
    {
        if (errorBlob)
        {
            OutputDebugStringA(rcast<const char*>(errorBlob->GetBufferPointer()));
            errorBlob->Release();
        }

        if (shaderBlob)
           shaderBlob->Release();

        return hr;
    }    

    *ppBlobOut = shaderBlob;

    return hr;
}
//--------------------------------------------------------------------------------------


export class RendererD3D11
{
public:
	ID3D11Device* md3dDevice_base = nullptr;
	ID3D11DeviceContext* md3dImmediateContext_base = nullptr;
	IDXGISwapChain* mSwapChain_base = nullptr;	

	// mRenderTargetView is the pointer to back buffer
	ID3D11RenderTargetView* mRenderTargetView_base = nullptr;
    ID3D11Texture2D* mDepthStencilBuffer_base = nullptr;

	ID3D11DepthStencilView* mDepthStencilView = nullptr;

    D3D11_VIEWPORT mScreenViewport = {0};	


	ID3D11Device1*          md3dDevice = nullptr;
	ID3D11DeviceContext1*   md3dImmediateContext = nullptr;
	IDXGISwapChain1*        mSwapChain = nullptr;
	ID3D11RenderTargetView* mRenderTargetView = nullptr;
    ID3D11Texture2D*		mDepthStencilBuffer = nullptr;

	//---
	int m_msaa_sample_count = 1;	
	int m_msaa_quality_level = 0;

	//---------------------------------------
	HWND m_render_window = nullptr;

private:
	void z_resize_helper()
	{
		HRESULT hr;
		//-------------------------------
		// Common in setup and resize

		// Create a render-target view. Use the back buffer address to create the render target
	#ifdef D3D11_NEW
		ID3D11Texture2D1* backBuffer = nullptr;
		// Get a pointer to the back buffer
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D1), rcast<void**>(&backBuffer));

		// Create a render-target view. Use the back buffer address to create the render target
		hr = md3dDevice->CreateRenderTargetView( backBuffer, nullptr, &mRenderTargetView_base );
		hr = md3dDevice->CreateRenderTargetView1( backBuffer, nullptr, &mRenderTargetView );
	#else

		ID3D11Texture2D* backBuffer = nullptr;
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		hr = md3dDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView_base);
	#endif

		SAFE_RELEASE(backBuffer);



		//-------------------------------

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};	
		depthStencilDesc.Width     = g_ws.width;
		depthStencilDesc.Height    = g_ws.height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count   = m_msaa_sample_count;
		depthStencilDesc.SampleDesc.Quality = m_msaa_quality_level;
		depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0; 
		depthStencilDesc.MiscFlags      = 0;

		hr = md3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer_base);
		//hr = mDepthStencilBuffer_base->QueryInterface( __uuidof(IDXGISwapChain4), rcast<void**>(&mDepthStencilBuffer));
		hr = com_uuid_cast(mDepthStencilBuffer, mDepthStencilBuffer_base);


		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = depthStencilDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		hr = md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, &descDSV, &mDepthStencilView);

		//hr = md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView);


		//-------------------------------
		// Common from setup
		// Bind the render target view and depth/stencil view to the pipeline. Set the render target as the back buffer
		md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView_base, mDepthStencilView);
		//hr = mRenderTargetView->QueryInterface( __uuidof(IDXGISwapChain4), rcast<void**>(&mRenderTargetView_base) );
		hr = com_uuid_cast(mRenderTargetView, mRenderTargetView_base);


		//vp.width, vp.height
		//RECT rc;
		//GetClientRect( g_hWnd, &rc );
		//UINT width = rc.right - rc.left;
		//UINT height = rc.bottom - rc.top;

		// Setup the viewport
		D3D11_VIEWPORT vp = {0};
		vp.TopLeftX = scast<float>(0);
		vp.TopLeftY = scast<float>(0);
		vp.Width = scast<float>(g_ws.width);
		vp.Height = scast<float>(g_ws.height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;

		md3dImmediateContext->RSSetViewports(1, &vp);
		//-------------------------------

	#if 1
		// Perspective Projection
		// Initialize the projection matrix

		//mProj = DirectX::XMMatrixPerspectiveFovLH( DirectX::XM_PIDIV2, mScreenViewport.Width / mScreenViewport.Height, 0.01f, 100.0f );
		// The window resized, so update the aspect ratio and recompute the projection matrix.
		// If mProj is of type DirectX::XMFLOAT4X4
		//DirectX::XMMATRIX P
		//DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(0.25f*mf::k_pi<float>(), aspect_ratio(), 1.0f, 1000.0f);
		//mProj = DirectX::XMMatrixPerspectiveFovLH(0.25f*mf::k_pi<float>(), aspect_ratio(), 1.0f, 1000.0f);	
		//DirectX::XMStoreFloat4x4(&d3d11::gd3dApp->mProj, P);
		//DirectX::XMStoreFloat4x4(&mProj, P);

		//mProj = DirectX::XMMatrixPerspectiveFovLH(0.25f*mf::k_pi<float>(), aspect_ratio(), 1.0f, 1000.0f);
	
	#endif
	}



public:
	fresult<bool> init(HWND hWnd)
	{
		m_render_window = hWnd;
		if (!m_render_window) { return fresult(false, q_finfo("Window Handle passed to init is null.\n")); }	

		HRESULT hr = S_OK;

		// Create the device and device context.
		UINT createDeviceFlags = 0;
	#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif
		//createDeviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// D3D 11.1 requires minimum Windows 7 SP1. Only D3D 11.1 and above supported.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			//D3D_FEATURE_LEVEL_12_1,
			//D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
		};
		UINT numFeatureLevels = q_array_size(featureLevels);
		D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_1;



		//D3D_DRIVER_TYPE driverTypes[] =
		//{
		//	D3D_DRIVER_TYPE_HARDWARE,
		//	//D3D_DRIVER_TYPE_WARP,
		//	//D3D_DRIVER_TYPE_REFERENCE,
		//};
		//UINT numDriverTypes = ARRAYSIZE( driverTypes );
		//for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ ) {
		//    md3dDriverType = driverTypes[driverTypeIndex];
		//	//D3D11CreateDevice()
		//}
		D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;



		// Check AntiAliasing level
		// Check 4X MSAA quality support for our back buffer format. All Direct3D 11 capable devices 
		// support 4X MSAA for all render target formats, so we only need to check quality support.
		//msaa_sample_count: 1, 2, 4, 8, 16, 32
		DXGI_FORMAT swap_chain_buffer_format = DXGI_FORMAT_R8G8B8A8_UNORM;

		//print("{}, {}\n", g_rcfg.msaa_enable, g_rcfg.msaa_samples);	
	
		//=== g_rcfg.msaa_samples = flib::clamp(g_rcfg.msaa_samples, 0, D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT);	

		// Check multisampling level supported by device
		ID3D11Device* test_device = nullptr;
		hr = D3D11CreateDevice(nullptr, md3dDriverType, nullptr, createDeviceFlags, &featureLevels[0], numFeatureLevels,
								D3D11_SDK_VERSION, &test_device, &m_featureLevel, &md3dImmediateContext_base);
		if( FAILED(hr) )
		{
			return fresult(false, q_finfo("D3D11CreateDevice for D3D11.1 Failed.\n"));
		}


		// Check 4X MSAA quality support for our back buffer format. All Direct3D 11 capable devices support 4X MSAA for all render 
		// target formats, so we only need to check quality support.
		hr = test_device->CheckMultisampleQualityLevels(swap_chain_buffer_format, g_rcfg.msaa_samples, rcast<UINT*>(&m_msaa_quality_level));	

		while (m_msaa_quality_level <= 0)
		{
			g_rcfg.msaa_samples /= 2;
			hr = test_device->CheckMultisampleQualityLevels(swap_chain_buffer_format, g_rcfg.msaa_samples, rcast<UINT*>(&m_msaa_quality_level));
			//print("m_msaa_quality_level: {}, g_rcfg.msaa_samples: {}\n", m_msaa_quality_level, g_rcfg.msaa_samples);
			if (g_rcfg.msaa_samples == 1) { break; }
		}
		SAFE_RELEASE(test_device);
		// Update g_rcfg.msaa_samples
		//print("d3d11: m_msaa_quality_level: {}, g_rcfg.msaa_samples: {}\n", m_msaa_quality_level, g_rcfg.msaa_samples);

		// Use MSAA. 
		if (g_rcfg.msaa_enable && (m_msaa_quality_level > 0))
		{
			m_msaa_sample_count = g_rcfg.msaa_samples;
			// Valid range is between zero and one less than the level returned by ID3D11Device::CheckMultisampleQualityLevels.
			m_msaa_quality_level = m_msaa_quality_level-1;
		}
		else
		{
			// CheckMultisampleQualityLevels() for g_rcfg.msaa_samples/2 values till m_msaa_quality_level is 1 or g_rcfg.msaa_samples is 1 in loop
			m_msaa_sample_count = 1;	
			m_msaa_quality_level = 0;
		}



		// Fill out a DXGI_SWAP_CHAIN_DESC struct to describe our swap chain.
		// create a struct to hold information about the swap chain
		//---
		DXGI_SWAP_CHAIN_DESC sd_base = {};        
		sd_base.BufferDesc.Width = g_ws.width;
		sd_base.BufferDesc.Height = g_ws.height;
		sd_base.BufferDesc.RefreshRate.Numerator = 60;
		sd_base.BufferDesc.RefreshRate.Denominator = 1;     
		sd_base.BufferDesc.Format = swap_chain_buffer_format;   
		sd_base.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd_base.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd_base.SampleDesc.Count = m_msaa_sample_count;
		sd_base.SampleDesc.Quality = m_msaa_quality_level;
		sd_base.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd_base.BufferCount = 1;
		sd_base.OutputWindow = m_render_window;
		//sd_base.Windowed   = true;
		sd_base.Windowed     = !g_ws.fullscreen;        
		sd_base.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
		//sd.Flags      = 0;
		sd_base.Flags		= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching			

		// D3D11.1
		//If you request a D3D_FEATURE_LEVEL_11_1 device on a computer with only the Direct3D 11.0 runtime, D3D11CreateDeviceAndSwapChain immediately exits
		//with E_INVALIDARG. To safely request all possible feature levels on a computer with the DirectX 11.0 or DirectX 11.1 runtime, use this code:
		hr = D3D11CreateDeviceAndSwapChain(nullptr, md3dDriverType, nullptr, createDeviceFlags, &featureLevels[0], numFeatureLevels, D3D11_SDK_VERSION, 
			&sd_base, &mSwapChain_base, &md3dDevice_base, &m_featureLevel, &md3dImmediateContext_base);

		if (FAILED(hr))
		{
			return fresult(false, q_finfo("D3D11CreateDevice for D3D11.1 Failed.\n"));
		}


		//hr = md3dDevice_base->QueryInterface(__uuidof(ID3D11Device5), rcast<void**>(&md3dDevice));
		hr = com_uuid_cast(md3dDevice, md3dDevice_base);
		hr = com_uuid_cast(md3dImmediateContext, md3dImmediateContext_base);
		hr = com_uuid_cast(mSwapChain, mSwapChain_base);
	

		//-----------------------------------------------------------
		// The remaining steps that need to be carried out for d3d creation also need to be executed every time 
		// the window is resized. Use z_resize_helper() method here to avoid code duplication.	
		z_resize_helper();

		return true;
	}

	void deinit()
	{
		// Restore all default settings.
		if(md3dImmediateContext) { md3dImmediateContext->ClearState(); }
	
		SAFE_RELEASE(mDepthStencilView);
		SAFE_RELEASE(mDepthStencilBuffer);
		SAFE_RELEASE(mRenderTargetView);

		SAFE_RELEASE(mSwapChain);	

		SAFE_RELEASE(md3dImmediateContext);

		SAFE_RELEASE(md3dDevice);

		//SAFE_RELEASE(WireFrame);


		SAFE_RELEASE(md3dDevice_base);
		SAFE_RELEASE(md3dImmediateContext_base);
		SAFE_RELEASE(mSwapChain_base);
		SAFE_RELEASE(mRenderTargetView_base);
		SAFE_RELEASE(mDepthStencilBuffer_base);
	}


	bool setup() { return true; }

	void render(float dt)
	{
		// Clear backbuffer.
		//g_immediate_context->ClearRenderTargetView(g_render_target_view, rcast<const float*>(&Colors::Blue));
		float color[4] = { 1.0f, 0.0f, 0.3f, 1.0f };		//red, green, blue, alpha

		//static float current_time;
		//current_time += delta_time;
		//const float color[] = { (float)sin(current_time) * 0.5 + 0.5f, (float)cos(current_time) * 0.5 + 0.5f, 0.0f, 1.0f };
		md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, color);	

		// Clear depth and stencil buffers.
		md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void cleanup() {}

    void swap_buffers() { mSwapChain->Present(0, 0); }

    //void on_resize();

	void clear(bool clear_color, const gm::colorf& color, bool clear_depth, float depth_val, bool clear_stencil, int stencil_val)
	{
		uint clear_flag = 0;
		if (clear_color) { md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, color.data()); }
		if (clear_depth) { clear_flag = clear_flag|D3D11_CLEAR_DEPTH; }
		if (clear_stencil) { clear_flag = clear_flag|D3D11_CLEAR_STENCIL; }    
		md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, depth_val, scast<UINT8>(stencil_val));
	}

};

}