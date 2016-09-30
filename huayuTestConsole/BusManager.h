#pragma once

#include "FlyCapture2.h"
using namespace FlyCapture2;
#define	BUS_ERROR	-1
#define BUS_0K		0

class CBusManager
{
public:

			CBusManager();
			virtual ~CBusManager();

			virtual int GetNumOfCameras( unsigned int* pNumCameras );

			virtual int GetCameraFromIPAddress(IPAddress ipAddress, PGRGuid* pGuid );
			virtual int GetCameraFromIndex(unsigned int index, PGRGuid*     pGuid );
			virtual int GetCameraFromSerialNumber(unsigned int serialNumber,PGRGuid*     pGuid );
			virtual int GetCameraSerialNumberFromIndex(unsigned int  index,unsigned int* pSerialNumber );

			//Read usb port status for the port that the specified device is connected to
			virtual int GetPortStatus(PGRGuid guid,unsigned int* pValue );

			//Force a rescan of the buses. 
			virtual int RescanBus();

			//Force the camera with the specific MAC address to the specified IP address, subnet mask and default gateway. 
			static int ForceIPAddressToCamera(MACAddress macAddress,IPAddress ipAddress,IPAddress subnetMask,IPAddress defaultGateway );

			//Force all cameras on the network to be assigned sequential IP addresses on the same subnet as the netowrk adapters that they are connected to. 
			static int ForceAllIPAddressesAutomatically();

			//Force a camera on the network to be assigned an IP address on the same subnet as the netowrk adapters that it is connected to. 
			static int ForceAllIPAddressesAutomatically(unsigned int serialNumber);

			static int DiscoverAllCameras(CameraInfo* gigECameras,unsigned int* arraySize  );

			//Query CCP status on camera with corresponding PGRGuid. 
			bool IsCameraControlable(PGRGuid* pGuid);

		private:
			CBusManager( const CBusManager& );
			CBusManager& operator=( const CBusManager& );
};

