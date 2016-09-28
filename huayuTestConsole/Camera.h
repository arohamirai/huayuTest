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

	// ��ʼ����ж�����
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
//	//�����������
//public:
//	int setBrightness(double _value);
//	int setExposure(double _value);
//	int setSharpness(int _value);
//	int setShutter(double _value);
//	int setGain(double _value);

private:
	int m_machineID;
	IN_ADDR m_IP;					//���IP��ַ

//private:
//	CString m_serialNumber;			//�������
//	CString m_model;				//�������ϵ��
//	float	m_brightness;			//����
//	float	m_exposure;				//�ع�
//	int		m_sharpness;			//���
//
//	float	m_shutter;				//
//	float	m_gain;					//����

	FlyCapture2::CameraInfo camInfo;
public:
	int identifyCamera(void);

private:
	CString m_errorInfo;
};

