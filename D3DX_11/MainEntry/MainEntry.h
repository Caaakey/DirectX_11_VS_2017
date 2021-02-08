#pragma once

class MainEntry
{
public:
	MainEntry();
	~MainEntry();

private:
	std::vector<SceneObject*> m_Scenes;
	UINT m_SceneLength;

public:
	HRESULT Start();
	void Update();
	void Render();

	HRESULT AddScene(SceneObject* pScene);
	HRESULT RemoveScene(SceneObject* pScene);
};

