#include "stdafx.h"
#include "SampleScene.h"

SampleScene::SampleScene(const char* name)
	: SceneObject(name), pObject(nullptr)
{ }

SampleScene::~SampleScene()
{
	DestroyObject(pObject);
}

HRESULT SampleScene::Start()
{
	pObject = ObjectModel::CreateModel("Dummy");

	return S_OK;
}

void SampleScene::Update()
{
}

void SampleScene::Render()
{
}
