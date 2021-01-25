#pragma once
#include "Interface/IScene.h"

class MainEntry : public IScene
{
public:
	MainEntry();
	~MainEntry();

public:
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
};

