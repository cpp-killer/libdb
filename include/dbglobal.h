#ifndef __DBGLOBAL_H__
#define __DBGLOBAL_H__

/*c++ mysql headers*/
#ifdef OS_WIN32
// #include "mysql_connection.h"
// #include "mysql_driver.h"
// #include "mysql_error.h"
// #include "cppconn/connection.h"
// #include "cppconn/statement.h"
// #include "cppconn/resultset.h"
// #include "cppconn/exception.h"
// #include "cppconn/driver.h"
#pragma warning( disable : 4290 )

#else
// #include "mysql_connection.h"
// #include "mysql_driver.h"
// #include "cppconn/connection.h"
// #include "cppconn/driver.h"
// #include "cppconn/statement.h"
// #include "cppconn/resultset.h"
// #include "cppconn/exception.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <errno.h>
#include <vector>
#include "dbexception.h"
//必需把MyDefine.放到这，要不然在win下会报编译错误
#ifdef DB_STATIC
#include "MyDefine.h"
#endif
#ifdef OS_WIN32
#include <windows.h>
#endif


// #ifndef HAVE_STRUCT_TIMESPEC
// #define  HAVE_STRUCT_TIMESPEC

namespace jjdb {
	typedef unsigned int	uint32;
	typedef unsigned short	uint16;
	typedef unsigned long	uint64;

}

#ifdef OS_WIN32
typedef	_int64					LONG64;
typedef unsigned	_int64		ULONG64;
#endif

typedef unsigned short			WORD;
typedef unsigned long			DWORD;
typedef long					LONG;
typedef unsigned	long		ULONG;


#ifdef OS_UNIX
typedef long					LONG32;
typedef unsigned	long		ULONG32;
typedef	long	long			LONG64;
typedef unsigned long	long	ULONG64;
#endif



typedef struct ctxinfo {
	std::string usr;
	std::string pwd;
	std::string dbname;
	std::string ip;
	//std::string ip2;
	unsigned short port;
	//unsigned short port2;
	std::string charset;
}CTXINFO;

typedef struct conntx
{

}CTX;

enum dbty
{
	EEE_MYSQL = 1,
	EEE_DMDBS,
	EEE_HGODB,
	EEE_ORCLE,
	EEE_UNKON
};


#ifdef OS_UNIX
#define _MAX_PATH 256
#endif

#ifdef OS_UNIX
#undef NULL
#define NULL			0
#define _stricmp		strcasecmp
#define closesocket		close
#define TRACE			printf
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR	(-1)
#define SOCKET			int
	typedef int				HANDLE;
	typedef int				HWND;
#define SOCKADDR_IN		sockaddr_in
	typedef const char *	LPCTSTR;
	typedef const char *	LPCSTR;
	typedef char *			LPSTR;
	typedef void *			LPVOID;


#endif

#ifdef  OS_WIN32
	#define  OUTAPI __stdcall
	#ifndef DBDLL_EXPORT
		#define DBDLL  __declspec(dllexport)
	#else
		#define DBDLL  __declspec(dllimport)
	#endif
#else
	#define DLLMYSQL
	#define OUTAPI
#endif


typedef void(*DBCB)(void *arg);

#define  MDNM  "getDbMain"
#define  DLNM  "delDbMain"

class CBaseSQLRES
{
	inline int getRow(){ return this->nRow; };
	inline void setRow(const int row) {this->nRow = row; };
	
private:
	int nRow;
};


class dbbase
{
public:
	dbbase()
	{

	}

	inline void  setSQL(std::string const &sql) { this->m_sSQL = sql; }
	virtual void outSrvVersion() throw (dbexception)= 0;
	virtual int	initDB(const ctxinfo &info) throw (dbexception) = 0;
	virtual int connDB() throw (dbexception) = 0;
	virtual int initDB() throw (dbexception) = 0;
	virtual int connDB(const ctxinfo &info) throw (dbexception) = 0;
	virtual int setCharSet(std::string const &En) throw (dbexception) = 0;
	virtual int	setAutoCommitOK() throw (dbexception) = 0;
	virtual int	setAutoCommitNo() throw (dbexception) = 0;
	/*not query ! available insert & update & alter .... , if you want select, please use to excuteQuery api!!*/
	virtual int excuteSQL(const std::string &sql) throw (dbexception) = 0;
	virtual int updateDB(const std::string &sql) throw (dbexception) = 0;
	virtual int	excuteQuery(const std::string &isql, const int &fields = 0) throw (dbexception) = 0;
	virtual void foreachDB() throw (dbexception) = 0;
	virtual int Commit() throw (dbexception) = 0;
	virtual int RollBack() throw (dbexception) = 0;
	virtual int AffairBegin() throw (dbexception) = 0;
	virtual int AffairStop() throw (dbexception) = 0;
	

	virtual int StoreResult() throw (dbexception) = 0; //遍历结果
	virtual void SetNumRows(const ULONG64 &rows) throw (dbexception) = 0 ;
	virtual void SetNumFields(const ULONG64 &fields) throw (dbexception) = 0 ;
	virtual ULONG64 getNumRows() throw (dbexception) = 0; //获取行数
	virtual ULONG64 getNumFields() throw (dbexception) = 0;//获取当前行的列数
	virtual int StoreResultRow(const int &row, std::vector<std::string> &cols) throw (dbexception) = 0;
	virtual int freeResult()  throw (dbexception)= 0 ;//删除结果集

	virtual std::string getDBString(const size_t &co) throw (dbexception) = 0;
	virtual void closeDB() throw (dbexception) = 0;
	virtual void destoryDB() throw (dbexception) = 0;
	virtual void setDataBufDB(jjdb::uint32 column, \
		void **values, \
		jjdb::uint16 valtype, \
		jjdb::uint32 size, \
		size_t *len) throw (dbexception) = 0;

	virtual std::string getDbDesc() = 0;
	virtual const char* ErrorStr() throw (dbexception) = 0;



	//业务
	//virtual int RecordDate(LONG key, char* farmId, char* grpId, char _val[32]) throw (dbexception) = 0;
	//virtual int UpdateRecordDate(LONG key, char* farmId, SYSTEMTIME curtime) throw (dbexception) = 0;
	//virtual int GetFarmInfos(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetVirtualGroupInfos(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetTruelyGroupInfos(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetEnvironGroupInfos(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetPhvsInfos(void* _this, int m_nDepots, int (*fun)(void *, char *, char *, char *, char *, char *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetWindInfos(void* _this, int m_nDepots, int (*fun)(void *, char *, char *, char *, char *, char *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetThreodInfo(void* _this, int m_nDepots, int (*fun)(void *, char *, char *, char *, int)) throw (dbexception) = 0;
	//virtual int GetFactorStateInfo(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *, char *, char *) ) throw (dbexception) = 0;
	//virtual int GetDarkTimeFromNWP(void* _this, int m_nDepots, int(*fun)(void *, char *, char *, char *, char *)) throw (dbexception) = 0;
	//virtual int GetRecordInfos(void* _this, int (*fun)(void *, char *, char *), char *farmid, int nFlag) throw (dbexception) = 0;
	//virtual int InitDataFlagInfos(char *farmid) throw (dbexception) = 0;
	//virtual int InsertLog(char *farm_id,int data_type, SYSTEMTIME sysTime,int status,char *memo,char *model_no = 0) throw (dbexception) = 0;
#ifdef _YuCe2
	virtual int GetPRE5FzyData(void *_this, int(*fun)(void* ) throw (dbexception) ;
#else

#endif
	virtual  ~dbbase()
	{

	}

protected:

	ULONG64 m_fields;
	ULONG64 m_rows;
	std::string Desc;
	std::string m_sSQL;
};



#ifdef DBLIB_FUNS 

time_t systime_to_timet(const SYSTEMTIME& st)
{
	struct tm gm = {st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth-1, st.wYear-1900, st.wDayOfWeek, 0, 0};
	return mktime(&gm);
}

/*	
**time_t转SYSTEMTIME
*/
SYSTEMTIME time_to_system(time_t t)
{
	tm temptm = *localtime(&t);

	SYSTEMTIME st;

	st.wYear = (WORD)(1900 + temptm.tm_year);
	st.wMonth = (WORD)(1 + temptm.tm_mon);
	st.wDay = (WORD)temptm.tm_wday;
	st.wDayOfWeek = (WORD)(temptm.tm_mday);
	st.wHour = (WORD)(temptm.tm_hour);
	st.wMinute = (WORD)(temptm.tm_min);
	st.wSecond = (WORD)(temptm.tm_sec);
	st.wMilliseconds = 0;

	return st;
}

void GetLocalTime(SYSTEMTIME & SysTime)
{
	time_t tTime;
	time( &tTime );

	tm * pTime = localtime(&tTime);
	SysTime.wYear = pTime->tm_year + 1900;
	SysTime.wMonth = pTime->tm_mon + 1;
	SysTime.wDayOfWeek = pTime->tm_wday;
	SysTime.wDay = pTime->tm_mday;
	SysTime.wHour = pTime->tm_hour;
	SysTime.wMinute = pTime->tm_min;
	SysTime.wSecond = pTime->tm_sec;
	SysTime.wMilliseconds = 0;
}

#endif

#endif


