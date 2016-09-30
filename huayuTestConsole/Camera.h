#pragma once
#include "atlstr.h"
#include "Dbase.h"
#include "FlyCapture2.h"
using namespace FlyCapture2;
#define	CAM_ERROR	-1
#define	CAM_OK		0

class CCamera
{
public:
	CCamera(void);
	~CCamera(void);

	// 初始化、卸载相机
public:
	int loadCamera(void);
	int unLoadCamera(void);

public:
	int getParam(CDbase* pDbase);
	int setParam(CDbase* pDbase);
	int isCameraControlable(PGRGuid *pGRGuid, bool *controlable);

	virtual int Connect( PGRGuid* pGuid = NULL );
	virtual int Disconnect();
	virtual bool IsConnected();
	virtual int SetCallback(ImageEventCallback callbackFn,const void* pCallbackData = NULL );
	
	virtual int StartCapture(ImageEventCallback callbackFn = NULL,const void* pCallbackData = NULL );
	static int StartSyncCapture(unsigned int numCameras,const Camera **ppCameras,const ImageEventCallback *pCallbackFns = NULL,const void** pCallbackDataArray = NULL );
	virtual int RetrieveBuffer( Image* pImage );
	virtual int StopCapture();

	virtual int GetStats( CameraStats* pStats );
	virtual int ResetStats();


public:
	CString getLastErrorInfo();
private:
	void transErrorInfo(FlyCapture2::Error &e);

public:
	FlyCapture2::CameraInfo m_camInfo;

private:
	CString m_errorInfo;
};

