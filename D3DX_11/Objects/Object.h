#pragma once
#include "stdafx.h"

class Object
{
public:
	static Object* CreateObject(std::string name);
	static void DestroyObject(Object* pObject);

public:
	Object();
	~Object();

private:
	Property(std::string, Name)

};

