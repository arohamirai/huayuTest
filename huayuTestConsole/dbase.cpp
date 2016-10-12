#include "Dbase.h"

CDbase::CDbase()
{
	CoInitialize(NULL);
}

CDbase::~CDbase()
{
	CoUninitialize();
}

_ConnectionPtr CDbase::connectDB(CString strConn)
{


	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");		//创建Connection对象
	HRESULT hr1 = m_pCommand.CreateInstance(_T("ADODB.Command"));		//创建Command对象
	HRESULT hr2 = m_pRecordset.CreateInstance(_T("ADODB.Recordset"));	//创建RecordSet对象

	if(!SUCCEEDED(hr) || !SUCCEEDED(hr1) || !SUCCEEDED(hr2))
	{
		m_errorInfo = _T("数据库初始化失败!");
		disConnectDB();
		return NULL;
	}

	// 建立连接数据库
	try
	{
		HRESULT hr = m_pConnection->Open((_bstr_t)strConn,"","",adModeUnknown);
	}
	catch (_com_error e)
	{
		transErrorInfo(e);
		disConnectDB();
		return NULL;
	}
	return m_pConnection;
}


int CDbase::disConnectDB(void)
{
	if (NULL != m_pRecordset && m_pRecordset->State == adStateOpen)
	{
		m_pRecordset->Close();
		m_pRecordset.Release();
		m_pRecordset = NULL;
	}
	if (NULL != m_pCommand && m_pCommand->State == adStateOpen)
	{
		m_pCommand.Release();
		m_pCommand = NULL;
	}
	if (NULL != m_pConnection && m_pConnection->State == adStateOpen)
	{
		m_pConnection->Close();
		m_pConnection.Release();
		m_pConnection = NULL;
	}
	
	return 0;
}


int CDbase::excuteSQLByConn(CString strSQL)
{
	try
	{
		m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		transErrorInfo(e);
		return DB_ERROR;
	}
	return DB_OK;
}


int CDbase::excuteSQLByCmd(CString strSQL)
{
//	//存储过程名
//	_bstr_t storeProc(_T("procname"));
//	_CommandPtr pCommand;
//	pCommand.CreateInstance(_T("ADODB.Command"));
//	pCommand->ActiveConnection=m_pConnection;
//	//指定CommandTexe属性为存储过程名
//	pCommand->CommandText=storeProc;
//	//指定CommandType属性为存储过程类型
//	pCommand->CommandType=adCmdStoredProc;
//	//在给参数赋值前调用Refresh方法
//	pCommand->Parameters->Refresh();
//	//给存储过程的参数赋值
//	pCommand->Paramters->Item[_variant_t((long)1)]->Value=_variant_t((LPCTSTR)name);
//	//执行存储过程，返回_RecordsetPtr类型指针,因为在CommandText中指定了命令，在Execute方法中参数赋空值就可了
//	m_pRecordset=pCommand->Execute(NULL,NULL,adCmdStoredProc);
	return 0;
}

_RecordsetPtr CDbase::readBySet(CString strSQL)
{
	if (NULL != m_pRecordset)
	{
		m_pRecordset->Close();
	}

	try
	{
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenStatic,adLockReadOnly,adCmdText);
	}
	catch (_com_error e)
	{
		transErrorInfo(e);
		if (NULL != m_pRecordset && m_pRecordset->State == adStateOpen)
		{
			m_pRecordset->Close();
		}
		return NULL;
	}

	return m_pRecordset;
}


template <typename T> 
int CDbase::modifyBySet(CString strSQL, CString field, T _value)
{
	if (NULL != m_pRecordset)
	{
		m_pRecordset->Close();
	}

	try
	{
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenStatic,adLockReadOnly,adCmdText);
	}
	catch (_com_error e)
	{
		if (NULL != m_pRecordset && m_pRecordset->State == adStateOpen)
		{
			m_pRecordset->Close();
		}
		return DB_ERROR;
	}

	m_pRecordset->PutCollect((_variant_t)field,(_variant_t)(T)_value);
	m_pRecordset->Update();
	m_pRecordset->


	return DB_OK;
}

void CDbase::transErrorInfo(_com_error e)
{
	m_errorInfo.Format(_T("查询失败！\n错误编号: %08lx\n错误信息: %s\n错误源: %s\n错误描述: %s"),
		e.Error(),                                                  
		e.ErrorMessage(),                                    
		(LPCTSTR)e.Source(),                           
		(LPCTSTR)e.Description());     
}

CString CDbase::getLastErrorInfo()
{
	return m_errorInfo;
}