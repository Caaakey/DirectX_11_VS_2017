#pragma once
#define ALIGNED_MALLOC(type, name)	\
	name = (type*)_aligned_malloc(sizeof(type), (size_t)sizeof 16);	\
	new (name)type;					\

#define ALIGNED_FREE(type, name)	\
	name->~type();					\
	_aligned_free(name);			\
	name = nullptr;					\

#define Property(type, name)																	\
	public: __declspec(property(put = __typeToSet_##name, get = __typeToGet##name)) type name;	\
	void __typeToSet_##name(const type& value) { m_##name = value; }							\
	type __typeToGet##name() const { return m_##name; }											\
	private: type m_##name;																		\

#define ReadonlyProperty(type, name)															\
	public: __declspec(property(get = __typeToGet_##name)) type name;							\
	type __typeToGet_##name() const { return m_##name; }										\
	private: type m_##name;																		\

#define SAFE_DELETE(p)			{if(p) { delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) { (p)->Release(); (p) = nullptr;}}

#define ALIGNED_SAFE_FREE(p)			{if(p) { ALIGNED_FREE(p); (p) = nullptr;}}
#define ALIGNED_SAFE_RELEASE(p)			{if(p) { (p)->Release(); ALIGNED_FREE(p); (p) = nullptr;}}

#define RETURN_FAILED_MESSAGE(p)		{ MessageBox(0, p, 0, 0); return E_FAIL; }
