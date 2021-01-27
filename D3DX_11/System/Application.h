#pragma once
#include "stdafx.h"

class Application
{
private:
	const LPCWSTR ApplicationName = L"Sample Application";

	HINSTANCE m_hInstance;

	ReadonlyProperty(HWND, hWnd)

	Property(UINT, Width)
	Property(UINT, Height)

public:
	Application();
	~Application();

	HRESULT OnCreate(HINSTANCE hInstance, int CmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

