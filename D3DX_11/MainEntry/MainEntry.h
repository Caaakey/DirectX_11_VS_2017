#pragma once

class MainEntry : public IScene
{
public:
	MainEntry();
	~MainEntry();

private:
	std::vector<IScene*> m_Scenes;

public:
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
};

