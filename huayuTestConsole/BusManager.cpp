#include "BusManager.h"


CBusManager::CBusManager(void)
{
}


CBusManager::~CBusManager(void)
{
}

int CBusManager::GetNumOfCameras( unsigned int* pNumCameras )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetNumOfCameras(pNumCameras);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

int CBusManager::GetCameraFromIPAddress(IPAddress ipAddress, PGRGuid *pGuid )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetCameraFromIPAddress(ipAddress,pGuid);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}
int CBusManager::GetCameraFromIndex(unsigned int index, PGRGuid	*pGuid )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetCameraFromIndex(index,pGuid);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}
int CBusManager::GetCameraFromSerialNumber(unsigned int serialNumber,PGRGuid *pGuid )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetCameraFromSerialNumber(serialNumber,pGuid);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}
int CBusManager::GetCameraSerialNumberFromIndex(unsigned int index,unsigned int *pSerialNumber )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetCameraSerialNumberFromIndex(index,pSerialNumber);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}


int CBusManager::GetPortStatus(PGRGuid guid,unsigned int* pValue )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.GetUsbPortStatus(guid,pValue);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

bool CBusManager::IsCameraControlable(PGRGuid* pGuid )
{
	BusManager bus;
	FlyCapture2::Error e;
	bool contralable = false;

	e = bus.IsCameraControlable(pGuid,&contralable);

	return contralable;
}

int CBusManager::RescanBus()
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.RescanBus();

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

int CBusManager::ForceIPAddressToCamera(MACAddress macAddress,IPAddress ipAddress,IPAddress subnetMask,IPAddress defaultGateway )
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.ForceIPAddressToCamera(macAddress,ipAddress,subnetMask,defaultGateway);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

int CBusManager::ForceAllIPAddressesAutomatically()
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.ForceAllIPAddressesAutomatically();

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}


int CBusManager::ForceAllIPAddressesAutomatically(unsigned int serialNumber)
{
	BusManager bus;
	FlyCapture2::Error e;

	e = bus.ForceAllIPAddressesAutomatically(serialNumber);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

//Discover all cameras connected to the network even if they reside on a different subnet. 
int CBusManager::DiscoverAllCameras(CameraInfo* gigECameras,unsigned int* arraySize  )
{
	BusManager bus;
	FlyCapture2::Error e;
	
	e = bus.DiscoverGigECameras(gigECameras,arraySize);

	return (e == PGRERROR_OK)?BUS_0K:BUS_ERROR;
}

