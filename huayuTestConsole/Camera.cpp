#include "Camera.h"

using namespace FlyCapture2;

CCamera::CCamera(void)
{
	m_machine = 0;
}


CCamera::~CCamera(void)
{
}


int CCamera::loadCamera(void)
{
	return 0;
}


int CCamera::unLoadCamera(void)
{
	return 0;
}


int CCamera::getParam(CDbase* pDbase)
{
	
	return 0;
}


int CCamera::setParam(CDbase* pDbase)
{
	return 0;
}


int CCamera::identifyCamera(void)
{
	BusManager busManger;
	unsigned int NumofCameras;
	FlyCapture2::Error e;

	e = busManger.GetNumOfCameras(&NumofCameras);
	if (e != PGRERROR_OK)		
	{
		transErrorInfo(e);
		return CAM_ERROR;
	}





	return 0;
}


void CCamera::transErrorInfo(FlyCapture2::Error &e)
{
	m_errorInfo.Format(_T("相机出错！\n错误类型：%d\n"),e.GetType());

	CString errType, errDescription, errSupport;
	errDescription = e.GetDescription();
	errSupport = e.CollectSupportInformation();

	m_errorInfo = m_errorInfo + (_T("\n错误描述：")) + errDescription + (_T("\n帮助信息：")) + errSupport;
}

CString CCamera::getLastErrorInfo()
{
	return m_errorInfo;
}