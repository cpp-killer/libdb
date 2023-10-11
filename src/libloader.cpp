#include "libloader.h"

#ifdef OS_UNIX
#include <dlfcn.h> 
#endif //OS_UNIX

CLibLoader::CLibLoader(std::string& libname)
{
	m_Handle = NULL;
	//    m_refcount = 0;
	m_refcount = 1;
	m_LibName = libname;
	m_libver = 0;
};

CLibLoader::~CLibLoader()
{
	if (m_Handle)
	{
		m_refcount = 1;
		Unload();
	}
};

#ifdef OS_UNIX
int CLibLoader::Load(int mode)
{
	if (!m_Handle)
	{
		if ((mode != RTLD_NOW) && (mode != RTLD_LAZY))
			mode = RTLD_LAZY;

		char filename[_MAX_PATH] = { 0 };
		strcat(filename, m_LibName.c_str());

		m_Handle = dlopen(filename, mode);
		if (m_Handle == NULL)
		{
			printf( "LIB: unable to load library %s: info: %s\n", m_LibName.c_str(), dlerror());
			//m_log.print(LOG_ERROR, LOG_MOD_RUN, "LIB: 无法加载动态库 %s: info: %s\n", m_LibName.c_str(), dlerror());
			return -1;
		};

		//		m_refcount = 1;
	}

	return GetRefCount();
};

int CLibLoader::Load()
{
	return Load(RTLD_LAZY);
};

void* CLibLoader::GetFuncPtr(const char* module)
{
	void *ptr = NULL;

	if (m_Handle == NULL)
	{
		printf("LIB: unable to get function pointer: %s before library %s loaded\n", module, m_LibName.c_str());
		//m_log.print(LOG_WARNING, LOG_MOD_RUN, "LIB: 动态库 %s 未加载，无法获取接口 %s\n", m_LibName.c_str(), module);
		return NULL;
	}

	dlerror();	//clear errors
	ptr = (void *)dlsym(m_Handle, module);
	if (ptr == NULL)
	{
		printf("LIB: unable to get function point ( %s )\n", dlerror());
	}

	return ptr;
};

int CLibLoader::Unload()
{
	if (m_Handle == NULL)
		return 0;

	int refcount = DecRefCount();

	if (refcount == 0)
	{
		dlclose(m_Handle);
		m_Handle = NULL;
	}

	return refcount;
};

#endif //OS_UNIX 


#ifdef OS_WIN32
int CLibLoader::Load(int)
{
	return Load();
};

int CLibLoader::Load()
{
	if (NULL == m_Handle)
	{
		m_Handle = LoadLibrary(m_LibName.c_str());
		if (m_Handle == NULL)
		{
			printf("LIB: 无法加载动态库 %s info: %d, %s\n", m_LibName.c_str(), GetLastError(), strerror(errno));
			return -1;
		}

		//		m_refcount = 1;
	}

	return GetRefCount();
};

void* CLibLoader::GetFuncPtr(const char* module)
{
	void *ptr = NULL;

	if (m_Handle == NULL)
	{
		printf("LIB: 动态库 %s 未加载，无法获取接口 %s\n", m_LibName.c_str(), module);
		return NULL;
	};

	ptr = (void *)GetProcAddress((HINSTANCE)m_Handle, module);

	return ptr;
};

int CLibLoader::Unload()
{
	if (m_Handle == NULL)
		return 0;

	int refcount = DecRefCount();
	if (refcount == 0)
	{
		FreeLibrary((HINSTANCE)m_Handle);
		m_Handle = NULL;
	}

	return refcount;
};

#endif //OS_WINDOWS



