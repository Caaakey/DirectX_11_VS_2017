#pragma once
#include <string>
#include <vector>

class Component;
class Object
{
public:
	Object();
	~Object();

	void Update();
	void Render();

	std::string Name;

private:
	std::vector<Component*> m_Component;

public:
	template <typename ComponentType>
	inline ComponentType* GetComponent()
	{
		ComponentType* pResult = nullptr;
		for (Component* c : m_Component)
		{
			pResult = dynamic_cast<ComponentType*>(c);
			if (pResult) break;
		}

		return pResult;
	}

	template <typename ComponentType>
	inline ComponentType* AddComponent()
	{
		ComponentType* pResult = GetComponent<ComponentType>();
		if (!pResult)
		{
			pResult = new ComponentType(this);
			m_Component.emplace_back(pResult);
		}

		return pResult;
	}

	template <typename ComponentType>
	inline void RemoveComponent()
	{
		ComponentType* pResult = GetComponent<ComponentType>();
		if (pResult)
		{
			m_Component.erase(pResult);
			delete pResult;
		}
	}
};

