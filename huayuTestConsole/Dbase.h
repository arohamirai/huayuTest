#pragma once

#import "C:\Program Files\Common Files\System\Ado\msado15.dll" no_namespace rename("EOF","adoEOF")

#include "atlstr.h"

#define DB_ERROR	-1
#define	DB_OK		0

class CDbase
{
public:
	CDbase();
	~CDbase();

public:
	int excuteSQLByConn(CString strSQL);
	int excuteSQLByCmd(CString strSQL);

	_RecordsetPtr readBySet(CString strSQL);
	template <typename T> int modifyBySet(CString strSQL, CString field, T _value);
	_ConnectionPtr connectDB(CString strConn = _T("Driver={SQL Server};Server=LENOVO-PC01;Database=huayuTest;UID=sa;PWD=AISINIWDLFT"));
	int disConnectDB(void);

	CString getLastErrorInfo();


private:
	void transErrorInfo(_com_error e);

private:
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;

private:
	CString m_errorInfo;
public:
	
};

