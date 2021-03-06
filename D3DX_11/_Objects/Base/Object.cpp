#include "stdafx.h"
#include "Object.h"

#include "_Components/Base/Component.h"

Object::Object(std::string name)
	: Name(name)
{

}

Object::~Object()
{
	if (m_Component.size() != 0)
	{
		for (Component* c : m_Component)
			SAFE_DELETE(c);
	}

	std::vector<Component*>().swap(m_Component);
}

void Object::Update()
{
	for (Component* c : m_Component)
		c->Update();
}

void Object::Render()
{
	for (Component* c : m_Component)
		c->Render();
}
