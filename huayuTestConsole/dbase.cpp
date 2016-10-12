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


	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");		//����Connection����
	HRESULT hr1 = m_pCommand.CreateInstance(_T("ADODB.Command"));		//����Command����
	HRESULT hr2 = m_pRecordset.CreateInstance(_T("ADODB.Recordset"));	//����RecordSet����

	if(!SUCCEEDED(hr) || !SUCCEEDED(hr1) || !SUCCEEDED(hr2))
	{
		m_errorInfo = _T("���ݿ��ʼ��ʧ��!");
		disConnectDB();
		return NULL;
	}

	// �����������ݿ�
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
//	//�洢������
//	_bstr_t storeProc(_T("procname"));
//	_CommandPtr pCommand;
//	pCommand.CreateInstance(_T("ADODB.Command"));
//	pCommand->ActiveConnection=m_pConnection;
//	//ָ��CommandTexe����Ϊ�洢������
//	pCommand->CommandText=storeProc;
//	//ָ��CommandType����Ϊ�洢��������
//	pCommand->CommandType=adCmdStoredProc;
//	//�ڸ�������ֵǰ����Refresh����
//	pCommand->Parameters->Refresh();
//	//���洢���̵Ĳ�����ֵ
//	pCommand->Paramters->Item[_variant_t((long)1)]->Value=_variant_t((LPCTSTR)name);
//	//ִ�д洢���̣�����_RecordsetPtr����ָ��,��Ϊ��CommandText��ָ���������Execute�����в�������ֵ�Ϳ���
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
	m_errorInfo.Format(_T("��ѯʧ�ܣ�\n������: %08lx\n������Ϣ: %s\n����Դ: %s\n��������: %s"),
		e.Error(),                                                  
		e.ErrorMessage(),                                    
		(LPCTSTR)e.Source(),                           
		(LPCTSTR)e.Description());     
}

CString CDbase::getLastErrorInfo()
{
	return m_errorInfo;
}