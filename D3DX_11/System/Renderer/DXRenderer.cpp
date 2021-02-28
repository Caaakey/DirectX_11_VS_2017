#include "stdafx.h"

DXRenderer::DXRenderer()
	:m_Device(nullptr), m_DeviceContext(nullptr), m_DeviceFeatureLevel(D3D_FEATURE_LEVEL_1_0_CORE),
	m_SwapChain(nullptr),
	m_GPUMemorySize(0), m_GPUDescription(L""),
	m_Numerator(0), m_Denominator(1),
	m_BackBuffer(nullptr), m_DepthStencilView(nullptr), m_RenderTargetView(nullptr),
	isVsync(false), isFullScreen(false), isUseImGui(false)

#if defined(_DEBUG)
	, m_DebugDevice(nullptr)
#endif
{ }

DXRenderer::~DXRenderer()
{
	if (isUseImGui) {
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		isUseImGui = false;
	}

	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_BackBuffer);

	if (m_SwapChain)
		m_SwapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_DeviceContext);
	SAFE_RELEASE(m_Device);
}

HRESULT DXRenderer::Initialize(UINT width, UINT height)
{
	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		RETURN_FAILED_MESSAGE(L"CreateDXGIFactory ERROR");

	IDXGIAdapter* adapter;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
		RETURN_FAILED_MESSAGE(L"EnumAdapters ERROR");

	IDXGIOutput* adapterOutput;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
		RETURN_FAILED_MESSAGE(L"EnumOutputs ERROR");

	UINT modeCount = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, NULL
	))) RETURN_FAILED_MESSAGE(L"GetDisplayModeList ERROR");

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	if (FAILED(adapterOutput->GetDisplayModeList(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, displayModeList
	))) RETURN_FAILED_MESSAGE(L"GetDisplayModeListDESC ERROR");

	for (UINT i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == width;
		isCheck &= displayModeList[i].Height == height;

		if (isCheck)
		{
			m_Numerator = displayModeList[i].RefreshRate.Numerator;
			m_Denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc = { 0, };
	if (FAILED(adapter->GetDesc(&adapterDesc)))
		RETURN_FAILED_MESSAGE(L"GetDescAdapter ERROR");

	m_GPUMemorySize = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	m_GPUDescription = adapterDesc.Description;

	SAFE_DELETE_ARRAY(displayModeList);
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);

	return S_OK;
}

HRESULT DXRenderer::InitializeDeviceAndSwapChain(HWND hWnd)
{
	//	https://devblogs.microsoft.com/directx/dxgi-flip-model/
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (isVsync) {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = m_Numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = m_Denominator;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1u;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !isFullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, creationFlags
		, featureLevels
		, 1
		, D3D11_SDK_VERSION
		, &swapChainDesc
		, &m_SwapChain
		, &m_Device
		, NULL
		, &m_DeviceContext
	))) RETURN_FAILED_MESSAGE(L"D3D11CreateDeviceAndSwapChain ERROR");

	m_DeviceFeatureLevel = m_Device->GetFeatureLevel();

	return S_OK;
}

HRESULT DXRenderer::InitializeImGui(HWND hWnd)
{
	isUseImGui = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(m_Device, m_DeviceContext);

	return S_OK;
}

HRESULT DXRenderer::CreateBackBuffer(UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC buffer = { 0 };
	buffer.Width = width;
	buffer.Height = height;
	buffer.MipLevels = 1;
	buffer.ArraySize = 1;
	buffer.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	buffer.SampleDesc.Count = 1u;
	buffer.SampleDesc.Quality = 0;
	buffer.Usage = D3D11_USAGE_DEFAULT;
	buffer.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	buffer.CPUAccessFlags = 0;
	buffer.MiscFlags = 0;

	if (FAILED(m_Device->CreateTexture2D(&buffer, NULL, &m_BackBuffer)))
		RETURN_FAILED_MESSAGE(L"CreateTexture-buffer ERROR");

	ID3D11Texture2D* backBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer)))
		RETURN_FAILED_MESSAGE(L"GetBuffer ERROR");

	if (FAILED(m_Device->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView)))
		RETURN_FAILED_MESSAGE(L"CreateRenderTargetView ERROR");

	SAFE_RELEASE(backBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	if (FAILED(m_Device->CreateDepthStencilView(m_BackBuffer, &desc, &m_DepthStencilView)))
		RETURN_FAILED_MESSAGE(L"CreateDepthStencilView ERROR");

	SetRenderTarget(m_RenderTargetView, m_DepthStencilView);
	return S_OK;
}

void DXRenderer::SetRenderTarget(ID3D11RenderTargetView* pRtv, ID3D11DepthStencilView* pDsv)
{
	if (pRtv) pRtv = m_RenderTargetView;
	if (pDsv) pDsv = m_DepthStencilView;

	if (m_DeviceContext) m_DeviceContext->OMSetRenderTargets(1, &pRtv, pDsv);
}

void DXRenderer::Resize(UINT width, UINT height)
{
	if (!m_SwapChain) return;

	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_BackBuffer);

	m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	CreateBackBuffer(width, height);
}

static bool isShow = true;
const float m_ClearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
void DXRenderer::Clear()
{
	if (isUseImGui) {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow(&isShow);
	}

	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DXRenderer::Present()
{
	if (isUseImGui) {
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	m_SwapChain->Present(isVsync ? 1 : 0, 0);
}
