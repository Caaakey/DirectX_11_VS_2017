#include "stdafx.h"
#include "MainEntry.h"

MainEntry::MainEntry()
	:m_SceneLength(0)
{
}

MainEntry::~MainEntry()
{
	for (UINT i = 0; i < m_SceneLength; ++i)
		SAFE_DELETE(m_Scenes[i]);

	std::vector<SceneObject*>().swap(m_Scenes);
}

HRESULT MainEntry::Start()
{
	
	return S_OK;
}

void MainEntry::Update()
{
	if (_KeyCode->KeyDown(VK_ESCAPE)) PostQuitMessage(0);

	for (UINT i = 0; i < m_SceneLength; ++i)
		m_Scenes[i]->Update();
}

void MainEntry::Render()
{
	for (UINT i = 0; i < m_SceneLength; ++i)
		m_Scenes[i]->Render();
}

HRESULT MainEntry::AddScene(SceneObject * pScene)
{
	try
	{
		if (pScene == nullptr || pScene->Name.empty())
			throw;
	}
	catch (...)
	{

	}

	return S_OK;
}

HRESULT MainEntry::RemoveScene(SceneObject * pScene)
{
	return E_NOTIMPL;
}
