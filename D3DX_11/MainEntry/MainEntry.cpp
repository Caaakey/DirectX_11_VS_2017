#include "stdafx.h"
#include "MainEntry.h"

MainEntry::MainEntry()
{
}

MainEntry::~MainEntry()
{
	for (int i = 0, length = m_Scenes.size(); i < length; ++i)
		SAFE_DELETE(m_Scenes[i]);
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
