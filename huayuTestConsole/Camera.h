#pragma once
#include "atlstr.h"
#include "Dbase.h"
#include "FlyCapture2.h"

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

public:
	CString getLastErrorInfo();

private:
	void transErrorInfo(FlyCapture2::Error &e);
//	//相机参数设置
//public:
//	int setBrightness(double _value);
//	int setExposure(double _value);
//	int setSharpness(int _value);
//	int setShutter(double _value);
//	int setGain(double _value);

private:
	int m_machineID;
	IN_ADDR m_IP;					//相机IP地址

//private:
//	CString m_serialNumber;			//相机串号
//	CString m_model;				//相机所属系列
//	float	m_brightness;			//亮度
//	float	m_exposure;				//曝光
//	int		m_sharpness;			//锐度
//
//	float	m_shutter;				//
//	float	m_gain;					//增益

	FlyCapture2::CameraInfo camInfo;
public:
	int identifyCamera(void);

private:
	CString m_errorInfo;
};

