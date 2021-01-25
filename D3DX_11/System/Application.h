#pragma once
#include "stdafx.h"

class Application
{
public:
	const LPCWSTR ApplicationName = L"Sample Application";

	HWND m_hWnd;
	HINSTANCE m_hInstance;
	UINT m_Width;
	UINT m_Height;

public:
	Application();
	~Application();

	HRESULT OnCreate(HINSTANCE hInstance, int CmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

