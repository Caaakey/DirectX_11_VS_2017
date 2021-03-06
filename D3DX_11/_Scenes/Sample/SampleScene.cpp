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

bool isOpen = true;
void SampleScene::Update()
{
	pObject->Update();
}

void SampleScene::Render()
{
	pObject->Render();
}

void SampleScene::OnGUI()
{
	ImGui::Begin("Inspector", &isOpen, 0);
	{
		DirectX::XMFLOAT3 pos = (DirectX::XMFLOAT3)pObject->transform->Position;
		DirectX::XMFLOAT3 rot = (DirectX::XMFLOAT3)pObject->transform->Rotation;
		DirectX::XMFLOAT3 scl = (DirectX::XMFLOAT3)pObject->transform->Scale;

		if (ImGui::SliderFloat3("Position", (float*)&pos, -1.0f, 1.0f)) pObject->transform->Position = pos;
		if (ImGui::SliderFloat3("Rotation", (float*)&rot, -1.0f, 1.0f)) pObject->transform->Rotation = rot;
		if (ImGui::SliderFloat3("Scale", (float*)&scl, -1.0f, 1.0f)) pObject->transform->Scale = scl;
	}
	ImGui::End();
}
