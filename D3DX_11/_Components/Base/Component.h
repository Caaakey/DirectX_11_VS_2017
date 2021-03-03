#pragma once

class Object;
class Transform;
class Component
{
public:
	Component(Object* connector) : m_Object(connector), m_Transform((Transform*)connector) { }
	virtual ~Component() { }

	Component(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

	virtual void Update() {}
	virtual void Render() {}

	Object* GetConnector() const { return m_Object; }

protected:
	Object* m_Object = nullptr;
	Transform* m_Transform = nullptr;
};
