#include "stdafx.h"
#include "SampleScene.h"

SampleScene::SampleScene(const char* name)
	: SceneObject(name), pObject(nullptr)
{
}

SampleScene::~SampleScene()
{
	SAFE_DELETE(pObject);
}

HRESULT SampleScene::Start()
{
	pObject = new ObjectModel("Dummy");
	Components::Renderer* r = pObject->AddComponent<Components::Renderer>();

	r->SetMesh(PolygonUtility::CreateBox(DirectX::XMFLOAT3(1, 1, 1)));

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
