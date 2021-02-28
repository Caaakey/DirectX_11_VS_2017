#pragma once
#include "_Objects/Base/Object.h"
#include "_Objects/Base/Transform.h"

#define DestroyObject(object) { ObjectModel::DestoryModel(object);	object = nullptr; }

class ObjectModel :
	public Object, public Transform
{
public:
	static ObjectModel* CreateModel(std::string name);
	static void DestoryModel(ObjectModel* pObject);

	ObjectModel();
	virtual ~ObjectModel();

};

