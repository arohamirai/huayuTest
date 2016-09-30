#include "Camera.h"

using namespace FlyCapture2;

CCamera::CCamera(void)
{
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

int CCamera::Connect( PGRGuid* pGuid )
{
	return 0;
}
int CCamera::Disconnect()
{
	return 0;
}
bool CCamera::IsConnected()
{
	return 0;
}
int CCamera::SetCallback(ImageEventCallback callbackFn,const void* pCallbackData )
{
	return 0;
}

int CCamera::StartCapture(ImageEventCallback callbackFn,const void* pCallbackData )
{
	return 0;
}
int CCamera::StartSyncCapture(unsigned int numCameras,const Camera **ppCameras,const ImageEventCallback *pCallbackFns,const void** pCallbackDataArray)
{
	return 0;
}
int CCamera::RetrieveBuffer( Image* pImage )
{
	return 0;
}
int CCamera::StopCapture()
{
	return 0;
}

int CCamera::GetStats( CameraStats* pStats )
{
	return 0;
}
int CCamera::ResetStats()
{
	return 0;
}





















//int CCamera::identifyCamera(void)
//{
//	BusManager busManger;
//	unsigned int NumofCameras;
//	FlyCapture2::Error e;
//
//	e = busManger.GetNumOfCameras(&NumofCameras);
//	if (e != PGRERROR_OK)		
//	{
//		transErrorInfo(e);
//		return CAM_ERROR;
//	}
//
//
//
//
//
//	return 0;
//}


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

