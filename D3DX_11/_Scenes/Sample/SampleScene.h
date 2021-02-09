#pragma once

class SampleScene : public IScene
{
public:
	SampleScene();
	~SampleScene();

	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
};

