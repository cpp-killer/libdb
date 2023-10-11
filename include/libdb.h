#pragma once
#ifndef __LIBDB_H__
#define __LIBDB_H__
#include <stdio.h>
#include "dbglobal.h"
#include "libloader.h"
#include "ini.h"
#define  CONFIG_FP "libdb.conf"
#ifdef  OS_WIN32
	#pragma warning (disable:4290)
	#ifndef DBLIB_EXPORT
		#define DBLIB  __declspec(dllexport)
	#else
		#define DBLIB  __declspec(dllimport)
	#endif
#else
	#define DBLIB
#endif

#ifdef OS_WIN32
const std::string mysqllibname =  "libdbmysql.dll" ;
const std::string myoralibname =  "libdboracle.dll" ;
const std::string mydmlibname =  "libdbdm.dll" ;
const std::string myhgolibname =  "libdbpq.dll" ;
#else
const std::string mysqllibname =  "libdbmysql.so.1" ;
const std::string myoralibname =  "libdboracle.so.1" ;
const std::string mydmlibname =  "libdbdm.so.1" ;
const std::string myhgolibname =  "libdbpq.so.1" ;
#endif


typedef dbbase* (OUTAPI *DBFUNC)();
typedef void (OUTAPI *DBFUNCDEL)(dbbase*);

class DBLIB libdb/*:public dbbase*/
{
public:
	libdb(int &dbtype);
	libdb();
	~libdb();
	void DBSetConfigPath(const std::string config = "");
	void DBSetLibPath(const std::string &dbpath){ /*this->m_sDbLibPath = dbpath;*/ };
	int LoadDbLibrary(const std::string &fp = "") throw (dbexception);
	void dbGetVersion() throw (dbexception);;
	int	DBInit(const ctxinfo &info)  throw (dbexception);
//	int	DBInit(const FORECASR_DBInfs &info)  throw (dbexception);
	int DBConn() throw (dbexception);
	int DBAffairBegin() throw (dbexception);
	int DBAffairStop() throw (dbexception);
	int DBCloseAutoCommit(int b) throw (dbexception);
	int DBAffairCommit()throw (dbexception);
	int DBAffairRollBack()throw (dbexception);

	int dbSetCharSet(std::string const &En) throw (dbexception);
	int	dbSetAutoCommitOK() throw (dbexception);
	int	dbSetAutoCommitNo() throw (dbexception);
	int dbExcuteSQL(const char *isql)  throw (dbexception);
	int	dbQuery(const char *isql, const int &fields = 0) throw (dbexception);

	int dbStoreResult() throw (dbexception);
	int dbStoreResultRow(const int &row, vector<std::string> &cols) throw (dbexception);
	void SetNumRows(const ULONG64 &rows);
	void SetNumFields(const ULONG64 &fields);
	ULONG64 dbGetNumRow() throw (dbexception);
	ULONG64 dbGetNumFields() throw (dbexception);
	int dbFreeRuslt() throw (dbexception);

	void DBClose() throw (dbexception);

	const char* DBErrorStr() throw (dbexception) ;
	/*2022 2 23*/
#ifndef _YuCe2
	int DBGetPRE5FzyData(void *_this, int(*fun)(void* )) throw (dbexception) ;
#else

#endif
	
protected:

private:
//	std::string m_sDbLibList;
//	std::string m_sDbLibPath;
	DBFUNC dbInstance;
	dbbase *m_pDb;
	CLibLoader *m_pLibLoader;
	CTX m_ctx;
	int m_dbtype;
	std::string m_sConfigPath;
	ctxinfo info1, info2;
	bool m_bConnected;

};

#endif
