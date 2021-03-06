#include "stdafx.h"
#include "ObjectModel.h"

ObjectModel::ObjectModel(std::string name)
	: Object(name)
{
	if (!transform)
	{
		//	https://upcommons.upc.edu/bitstream/handle/2117/112381/04211023.pdf
		void* pVoid = _aligned_malloc(sizeof Transform, (size_t)sizeof 16);
		transform = new (pVoid)Transform();
	}
}

ObjectModel::~ObjectModel()
{
	if (transform) _aligned_free(transform);
}
