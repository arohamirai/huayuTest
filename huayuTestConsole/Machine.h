#pragma once
#include "Camera.h"
#include "IoControler.h"

#define	MACHINE_ERROR	-1
#define	MACHINE_OK		0


#define LINEMODULES_PER_MACHINE		2
#define	CAMERAS_PER_LINEARMODULE	2

class CMachine
{
public:
	CMachine(void);
	~CMachine(void);


public:
	CCamera			m_camera[LINEMODULES_PER_MACHINE*CAMERAS_PER_LINEARMODULE];
	CIoControler	m_IoControler[LINEMODULES_PER_MACHINE];


public:
	unsigned int m_mechineID;

public:
	static unsigned int threadProc(PVOID pParam);
};

