#include "Object.h"

Object* Object::CreateObject(std::string name)
{
	if (name.empty()) return nullptr;
	void* pObject = _aligned_malloc(sizeof(Object), (size_t)sizeof 16);

	return new (pObject)Object();
}

void Object::DestroyObject(Object * pObject)
{
	pObject->~Object();
	_aligned_free(pObject);
}

Object::Object()
{
}

Object::~Object()
{
}
