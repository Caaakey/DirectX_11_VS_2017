#include "stdafx.h"
#include "MainEntry.h"

MainEntry::MainEntry()
{
}

MainEntry::~MainEntry()
{
}

HRESULT MainEntry::Start()
{
	return S_OK;
}

void MainEntry::Update()
{
	if (_KeyCode->KeyDown(VK_ESCAPE)) PostQuitMessage(0);
}

void MainEntry::Render()
{
}
