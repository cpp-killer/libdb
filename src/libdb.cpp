#include "libdb.h"


int libdb::dbSetCharSet(std::string const &En) throw (dbexception)
{
	m_pDb->setCharSet(En);
	return 0;
}

libdb::libdb(int &dbtype):m_dbtype(dbtype)
{
//	m_sDbLibList = "";
	m_bConnected = false;
	this->m_pDb = NULL;
}

libdb::libdb()
{
//	m_sDbLibList = "";
	m_bConnected = false;
	this->m_pDb = NULL;
}

libdb::~libdb()
{	
//	m_pDb->destoryDB();
	DBFUNCDEL delDb = (DBFUNCDEL)m_pLibLoader->GetFuncPtr(DLNM);
	delDb(m_pDb);
	//if (delDb != NULL)
	//	delDb(m_pDb);

	if (m_pLibLoader != NULL)
	{
		m_pLibLoader->Unload();
		delete m_pLibLoader;
	}
	m_pDb = NULL;
	m_pLibLoader = NULL;
}


void libdb::DBSetConfigPath( const std::string config )
{
	this->m_sConfigPath = config;
}


int libdb::LoadDbLibrary(const std::string &fp) throw (dbexception)
{

	CIni Ini(/*m_sConfigPath*/"./config/db.ini");
	
	std::string m_sDbLibList = "./";
#ifdef OS_WIN32
	char LibPath[128] = {0};
	size_t RetSize;
	getenv_s(&RetSize, LibPath, 127, "CCSOSD" );
	std::string slib = Ini.ReadString("libdb", "libname", "libdbmysql.dll");
	//m_sDbLibList += "\\";
#endif

#ifdef OS_UNIX
	std::string slib = Ini.ReadString("libdb", "libname", "libdbmysql.so");
	//m_sDbLibList = secure_getenv("CCSOSD");
#endif
	m_sDbLibList += slib;

	m_pLibLoader = new CLibLoader(m_sDbLibList);
	if(-1 == m_pLibLoader->Load())
		throw dbexception(-2, "Load %s error!", m_sDbLibList.c_str());

	DBFUNC pfuc = (DBFUNC)m_pLibLoader->GetFuncPtr(MDNM);
	if (pfuc == NULL )
	{
#ifdef WIN32
		printf("get db main func err (func name :%s->%u) !\n", MDNM, GetLastError());
		throw dbexception(GetLastError(), "get db main func err (func name :%s ) !\n", MDNM);
#else
		printf("get db main func err (func name :%s->%s) !\n", MDNM, dlerror());
		throw dbexception(errno, "get db main func err (func name :%s->%s) !\n", MDNM, dlerror());
#endif
	}

	m_pDb = pfuc();
	if (m_pDb == NULL)
		throw dbexception(-1, "create %s db error!", m_sDbLibList.c_str());
	return 0;
}


int libdb::DBInit(const ctxinfo &info)  throw (dbexception)
{


	//m_pDb->initDB();

//	m_pLibLoader->Unload();
//	std::cout << m_pDb->getDbDesc() << std::endl;
	return m_pDb->initDB();

}
#if 0
int libdb::DBInit( const FORECASR_DBInfs &info ) throw (dbexception)
{
	info1.ip = info.strip1;
	info1.dbname = info.strName;
	info1.port = info.port;
	info1.usr = info.strUser;
	info1.pwd = info.strPassWord;
	std::cout << info1.ip << " : " << info1.port << "; " << info1.dbname  << std::endl;
	return DBInit(info1);
}
#endif

int libdb::DBConn() throw (dbexception)
{
	return m_pDb->connDB(info1);
}


int libdb::dbSetAutoCommitOK() throw (dbexception)
{
	return m_pDb->setAutoCommitOK();
}

int libdb::dbSetAutoCommitNo() throw (dbexception)
{	
	return m_pDb->setAutoCommitNo();
}

int libdb::dbExcuteSQL(const char *isql) throw (dbexception)
{
	return	m_pDb->excuteSQL(isql);
}

int libdb::dbQuery(const char *isql, const int &fields)  throw (dbexception)
{
	if (fields == 0)
		return m_pDb->excuteSQL(isql);
	else
		return m_pDb->excuteQuery(isql, fields);
}


void libdb::dbGetVersion()  throw (dbexception)
{
	m_pDb->outSrvVersion();
}


void libdb::DBClose() throw (dbexception)
{
	if(m_pDb != NULL)
		m_pDb->closeDB();
}

int libdb::DBAffairBegin() throw (dbexception)
{
	return m_pDb->AffairBegin();
}

int libdb::DBAffairStop() throw (dbexception)
{
	return m_pDb->AffairStop();
}

int libdb::DBCloseAutoCommit(int b) throw (dbexception)
{
	(b)?m_pDb->setAutoCommitNo():m_pDb->setAutoCommitOK();
	return 0;
}

int libdb::DBAffairCommit() throw (dbexception)
{
	return m_pDb->Commit();
}

int libdb::DBAffairRollBack() throw (dbexception)
{
	return m_pDb->RollBack();
}


const char* libdb::DBErrorStr() throw (dbexception)
{
	return m_pDb->ErrorStr();
}

int libdb::dbStoreResult() throw (dbexception)
{
	return m_pDb->StoreResult();
}

int libdb::dbStoreResultRow( const int &row, vector<std::string> &cols ) throw (dbexception)
{
	return m_pDb->StoreResultRow(row, cols);
}

void libdb::SetNumRows( const ULONG64 &rows )
{
	m_pDb->SetNumRows(rows);
}

void libdb::SetNumFields( const ULONG64 &fields )
{
	m_pDb->SetNumFields(fields);
}

ULONG64 libdb::dbGetNumRow() throw (dbexception)
{
	return m_pDb->getNumRows();
}

ULONG64 libdb::dbGetNumFields() throw (dbexception)
{
	return m_pDb->getNumFields();
}

int libdb::dbFreeRuslt() throw (dbexception)
{
	return m_pDb->freeResult();
}



//int libdb::DBInsertLog( char *farm_id,int data_type, SYSTEMTIME sysTime,int status,char *memo,char *model_no) throw (dbexception)
//{
//	return m_pDb->InsertLog(farm_id, data_type, sysTime, status, memo, model_no);
//}

