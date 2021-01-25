#include "stdafx.h"
#include "MainEntry/MainEntry.h"
#include "System/Application.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MainEntry m_Main = MainEntry();
	Application m_Application = Application();

	if (FAILED(m_Application.OnCreate(hInstance, nCmdShow))) return FALSE;

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
			m_Main.Render();
		}
	}

	return (int)msg.wParam;
}
