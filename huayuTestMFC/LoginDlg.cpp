// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "huayuTestMFC.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_tryCounts = 0;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_USERNAME,m_userName);
	DDX_Text(pDX,IDC_USERPWD,m_password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &CLoginDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序 


void CLoginDlg::OnBnClickedOk()
{
	// TODO:
	if (NULL != m_pRecordset && m_pRecordset->State == adStateOpen)
	{
		m_pRecordset->Close();
		m_pRecordset.Release();
		m_pRecordset = NULL;
	}

	if (NULL != m_pConnection && m_pConnection->State == adStateOpen)
	{
		m_pConnection->Close();
		m_pConnection.Release();
		m_pConnection = NULL;
	}
	CDialogEx::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: 

	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, 
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,220,LWA_ALPHA);

	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");//创建Connection对象
	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL,_T("数据库初始化失败!"),_T("致命错误"),MB_ICONERROR|MB_OK);
		return TRUE;
	}

	try
	{
		CString strSQL = _T("Driver={SQL Server};Server=LENOVO-PC01;Database=huayuTest;UID=sa;PWD=AISINIWDLFT");
		hr = m_pConnection->Open((_bstr_t)strSQL,"","",adModeUnknown);
	}
	catch (_com_error e) //COM错误取得,当执行COM功能的时候，如果出错，可以捕捉到_com_error的异常
	{
		CString strComError;
		strComError.Format(_T("数据库连接失败，请检查！！！\n错误编号: %08lx\n错误信息: %s\n错误源: %s\n错误描述: %s"),
			e.Error(),								// 错误编号
			e.ErrorMessage(),						// 错误信息
			(LPCTSTR) e.Source(),					// 错误源
			(LPCTSTR) e.Description());				// 错误描述     
		::MessageBox(NULL,strComError,_T("致命错误"),MB_ICONERROR|MB_OK);

		EndDialog(IDCANCEL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CLoginDlg::OnBnClickedLogin()
{
	// TODO:
	//char *p = new char[10*4096];
	if (m_tryCounts == 5)
	{
		::MessageBox(NULL,_T("你的重试次数已达到最大值，请稍后在尝试登陆，程序将退出！"),_T("错误"),MB_ICONERROR|MB_OK);
		CDialogEx::OnCancel();
		return;
	}


	UpdateData(TRUE);

	m_userName.TrimLeft();
	m_userName.TrimRight();
	m_password.TrimLeft();
	m_password.TrimRight();

	if (m_userName == _T("") || m_password == _T(""))
	{
		::MessageBox(NULL,_T("用户名或密码不能为空！"),_T("警告"),MB_ICONERROR|MB_OK);
		return;
	}

	HRESULT hr = m_pRecordset.CreateInstance("ADODB.Recordset");
	if(!SUCCEEDED(hr))
	{
		::MessageBox(NULL,_T("数据库初始化失败!"),_T("致命错误"),MB_ICONERROR|MB_OK);
		return;
	}

	CString strSQL;
	strSQL = _T("select * from userInfoTable where userName = '") + m_userName + _T("'");
	try
	{
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),adOpenStatic,adLockReadOnly,adCmdText);
	}
	catch (_com_error e)
	{
		::MessageBox(NULL,e.Description(),_T("致命错误"),MB_ICONERROR|MB_OK);
		if (NULL != m_pRecordset && m_pRecordset->State == adStateOpen)
		{
			m_pRecordset->Close();
			m_pRecordset.Release();
			m_pRecordset = NULL;
		}
		return;
	}

	if(m_pRecordset->GetRecordCount() != 1)
	{
		::MessageBox(NULL,_T("查不到该用户，请核实并重试！"),_T("警告"),MB_ICONWARNING|MB_OK);
		m_pRecordset->Close();
		m_pRecordset.Release();
		m_pRecordset = NULL;

		m_tryCounts++;
		return;
	}
	else
	{
		m_pRecordset->MoveFirst();

		if (m_password != m_pRecordset->GetCollect(_T("userPwd")).bstrVal)
		{
			::MessageBox(NULL,_T("密码错误，请检查并重试！"),_T("警告"),MB_ICONWARNING|MB_OK);
			m_pRecordset->Close();
			m_pRecordset.Release();
			m_pRecordset = NULL;

			m_tryCounts++ ;
			return;
		}
		else
		{
			m_userType = m_pRecordset->GetCollect(_T("userName")).bstrVal;
			m_pRecordset->Close();
			m_pRecordset.Release();
			m_pRecordset = NULL;
		}
	}
	
	if (NULL != m_pConnection && m_pConnection->State == adStateOpen)
	{
		m_pConnection->Close();
		m_pConnection.Release();
		m_pConnection = NULL;
	}
	CDialogEx::OnOK();
}
