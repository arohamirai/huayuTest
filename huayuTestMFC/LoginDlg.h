#pragma once
#include "stdafx.h"

// CLoginDlg �Ի���

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();

private:
	int m_tryCounts;
	CString m_userName;
	CString m_password;
	CString m_userType;

private:
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

public:
	virtual BOOL OnInitDialog();
	void OnBnClickedOk();
};
