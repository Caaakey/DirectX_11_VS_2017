#pragma once
#include "_Objects/ObjectModel.h"

class Component
{
public:
	Component(ObjectModel* connector)
		: object(connector), transform(connector->transform)
	{ }
	virtual ~Component() { }

	Component() = delete;
	Component(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

	virtual void Update() {}
	virtual void Render() {}

protected:
	ObjectModel* object = nullptr;
	Transform* transform = nullptr;
};
