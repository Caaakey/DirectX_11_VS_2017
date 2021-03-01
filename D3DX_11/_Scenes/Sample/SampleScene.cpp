#include "stdafx.h"
#include "SampleScene.h"

SampleScene::SampleScene(const char* name)
	: SceneObject(name), pObject(nullptr)
{
}

SampleScene::~SampleScene()
{
	DestroyObject(pObject);
}

HRESULT SampleScene::Start()
{
	pObject = ObjectModel::CreateModel("Dummy");
	Components::Renderer* r = pObject->AddComponent<Components::Renderer>();

	r->SetMesh(MeshUtility::CreateBox(DirectX::XMFLOAT3(1, 1, 1)));

	return S_OK;
}

void SampleScene::Update()
{
	pObject->Update();
}

void SampleScene::Render()
{
	pObject->Render();
}
