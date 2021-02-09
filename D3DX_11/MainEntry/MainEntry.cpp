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
			throw std::exception("Scene is Null or empty Name"); 

		pScene->Start();
		m_Scenes.emplace_back(pScene);
	}
	catch (const std::exception e)
	{
		MessageBoxA(Application::Get().hWnd, e.what(), NULL, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT MainEntry::RemoveScene(SceneObject * pScene)
{
	if (pScene == nullptr || pScene->Name.empty()) return E_FAIL;
	if (m_SceneLength == 0) return S_OK;

	for (auto iter = m_Scenes.begin(); iter != m_Scenes.end(); ++iter)
	{
		if ((*iter)->Name == pScene->Name)
		{
			delete (*iter);
			m_Scenes.erase(iter);

			break;
		}
	}

	return S_OK;
}
