#pragma once

class Object;
class Component
{
public:
	Component(Object* connector) : m_Connect(connector) { }
	virtual ~Component() { }

	Component(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

	virtual void Update() {}
	virtual void Render() {}

	Object* GetConnector() const { return m_Connect; }

protected:
	Object* m_Connect = nullptr;
};
