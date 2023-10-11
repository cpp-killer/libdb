#pragma once
#include "dbglobal.h"
#ifdef OS_UNIX
#include  <dlfcn.h>
#endif

class CLibLoader
{
public:
	CLibLoader(std::string& libname);
	~CLibLoader();

	int Load(int mode);
	int Load();
	int Unload();

	void *GetFuncPtr(const char *module);
	inline int GetRefCount() { return m_refcount; };
	inline int IncRefCount() { return ++m_refcount; };
	//	CONFIG_ITEM m_libveritem;
	int m_libver;

protected:
	void *m_Handle;
	std::string m_LibName;
	int  m_refcount;


protected:
	//    inline int IncRefCount(){ return ++m_refcount; };
	inline int DecRefCount() { return --m_refcount; };
private:

};

