#pragma once

class SampleScene : public SceneObject
{
public:
	SampleScene(const char* name);
	~SampleScene();

	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	ObjectModel* pObject;

};

