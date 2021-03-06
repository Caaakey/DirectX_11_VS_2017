#pragma once
#include "_Objects/Base/Object.h"
#include "_Objects/Base/Transform.h"

class ObjectModel : public Object
{
public:
	ObjectModel() = delete;
	ObjectModel(std::string name);
	virtual ~ObjectModel();

	Transform* transform;

};

