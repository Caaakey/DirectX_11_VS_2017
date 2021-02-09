#pragma once
#include "Interface/IScene.h"

class SceneObject : public IScene
{
public:
	SceneObject(const std::string name)
	{
		Name = name;
		Enable = true;
	}

private:
	Property(bool, Enable)
	Property(std::string, Name)
};