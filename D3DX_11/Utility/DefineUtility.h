#pragma once
#define ALIGNED_MALLOC(type, name)	\
	name = (type*)_aligned_malloc(sizeof(type), (size_t)sizeof 16);	\
	new (name)type;					\

#define ALIGNED_FREE(type, name)	\
	name->~type();					\
	_aligned_free(name);			\
	name = nullptr;					\

#define SAFE_DELETE(p)			{if(p) { delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) { (p)->Release(); (p) = nullptr;}}

#define ALIGNED_SAFE_FREE(p)			{if(p) { ALIGNED_FREE(p); (p) = nullptr;}}
#define ALIGNED_SAFE_RELEASE(p)			{if(p) { (p)->Release(); ALIGNED_FREE(p); (p) = nullptr;}}
