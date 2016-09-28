#pragma once
#include "Camera.h"
#include "IoControler.h"

#define	MACHINE_ERROR	-1
#define	MACHINE_OK		0
class CMachine
{
public:
	CMachine(void);
	~CMachine(void);

public:
	static unsigned int isCameraOK(unsigned int machineID);



public:
	unsigned int m_mechineID;
private:
	CCamera			*m_camera;
	CIoControler	*m_IoControler;
};

