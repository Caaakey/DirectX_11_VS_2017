#pragma once
#include "stdafx.h"

class Application
{
public:
	static Application& Get() {
		static Application instance;
		return instance;
	}

	Application();
	Application(Application const&) = delete;
	~Application();

	void operator=(Application const&) = delete;

private:
	const LPCWSTR ApplicationName = L"Sample Application";

	HINSTANCE m_hInstance;

	ReadonlyProperty(HWND, hWnd)

	Property(UINT, Width)
	Property(UINT, Height)

public:
	HRESULT OnCreate(HINSTANCE hInstance, int CmdShow);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

