#include "stdafx.h"
#include "MainEntry/MainEntry.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Application* m_Application = &Application::Get();
	DXRenderer* m_Renderer = &DXRenderer::Get();

	if (FAILED(m_Application->OnCreate(hInstance, nCmdShow)))
		RETURN_FAILED_MESSAGE(L"Create Window Failed");

	if (FAILED(m_Renderer->Initialize(m_Application->Width, m_Application->Height)))		return FALSE;
	if (FAILED(m_Renderer->InitializeDeviceAndSwapChain(m_Application->hWnd)))				return FALSE;
	if (FAILED(m_Renderer->CreateBackBuffer(m_Application->Width, m_Application->Height)))	return FALSE;
	//if (FAILED(m_Renderer->InitializeImGui(m_Application->hWnd)))							return FALSE;

	MainEntry m_Main;
	if (FAILED(m_Main.Start()))	return FALSE;

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			_Timer->UpdateTime();

			m_Main.Update();

			m_Renderer->Clear();
			m_Main.Render();
			m_Renderer->Present();
		}
	}

	return (int)msg.wParam;
}
