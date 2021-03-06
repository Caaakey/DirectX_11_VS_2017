#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

class DXRenderer
{
public:
	static DXRenderer& Get() {
		static DXRenderer instance;
		return instance;
	}

	DXRenderer();
	DXRenderer(DXRenderer const&) = delete;
	~DXRenderer();

	void operator=(DXRenderer const&) = delete;
	
public:
	HRESULT Initialize(UINT width, UINT height);
	HRESULT InitializeDeviceAndSwapChain(HWND hWnd);
	HRESULT InitializeImGui(HWND hWnd);
	HRESULT CreateBackBuffer(UINT width, UINT height);

	void SetRenderTarget(ID3D11RenderTargetView* pRtv, ID3D11DepthStencilView* pDsv);
	void Resize(UINT width, UINT height);

	void Clear();
	void Present();

	void NewFrameOnGUI();
	void RenderOnGUI();
	bool IsUsedImGui() const { return isUseImGui; }

private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	IDXGISwapChain* m_SwapChain;

	SIZE_T m_GPUMemorySize;
	LPCWSTR m_GPUDescription;

	UINT m_Numerator;
	UINT m_Denominator;

	ID3D11Texture2D* m_BackBuffer;
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11RenderTargetView* m_RenderTargetView;

	D3D_FEATURE_LEVEL m_DeviceFeatureLevel;
	bool isVsync;
	bool isFullScreen;

	bool isUseImGui;

#if defined(_DEBUG)
	ID3D11Debug* m_DebugDevice;
#endif

public:
	ID3D11Device* GetDevice() const { return m_Device; }
	ID3D11DeviceContext* GetContext() const { return m_DeviceContext; }
};

