#include "ObjectModel.h"

ObjectModel * ObjectModel::CreateModel(std::string name)
{
	if (name.empty()) return nullptr;

	void* pObject = _aligned_malloc(sizeof(ObjectModel), (size_t)sizeof 16);
	return new (pObject)ObjectModel();
}

void ObjectModel::DestoryModel(ObjectModel * pObject)
{
	if (pObject == nullptr) return;

	pObject->~ObjectModel();
	_aligned_free(pObject);
}

ObjectModel::ObjectModel()
{
}

ObjectModel::~ObjectModel()
{
}
