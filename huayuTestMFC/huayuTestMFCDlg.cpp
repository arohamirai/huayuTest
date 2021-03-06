﻿
// huayuTestMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "huayuTestMFC.h"
#include "huayuTestMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChuayuTestMFCDlg 对话框




ChuayuTestMFCDlg::ChuayuTestMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChuayuTestMFCDlg::IDD, pParent)
{
	//
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChuayuTestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ChuayuTestMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &ChuayuTestMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChuayuTestMFCDlg 消息处理程序

BOOL ChuayuTestMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, 
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|WS_EX_LAYERED);
	SetLayeredWindowAttributes(0,220,LWA_ALPHA);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ChuayuTestMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CRect   rc;
		//GetClientRect( &rc );// 获取客户区
		//CPaintDC dc(this);
		//dc.FillSolidRect(&rc, RGB(199,237,199));   // 填充客户区颜色
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ChuayuTestMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ChuayuTestMFCDlg::OnBnClickedOk()
{
	// TODO: 

	LPCTSTR lpApplicationName= _T("C://Users//lenovo//Documents//Visual Studio 2010//Projects//huayuTestMFC//Debug//huayuTestConsole.exe");
	LPTSTR  lpCommandLine = _T(" huayuTest");

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL flag = CreateProcess(lpApplicationName,lpCommandLine,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi);
	if (!flag)
	{
		MessageBox(_T("启动图像计算程序失败！"));
		return;
	}
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	CDialogEx::OnOK();
}
