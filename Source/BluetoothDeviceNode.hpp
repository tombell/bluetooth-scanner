/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#ifndef _BLUETOOTHDEVICENODE_HEADER_
#define _BLUETOOTHDEVICENODE_HEADER_

#include <windows.h>
#include <bthdef.h>
#include <bluetoothapis.h>

class CBluetoothDeviceNode
{
	public:

		CBluetoothDeviceNode(void);
		~CBluetoothDeviceNode(void);

		bool SetNextNode(CBluetoothDeviceNode* pNextNode);
		CBluetoothDeviceNode* GetNextNode(void);

		bool SetPreviousNode(CBluetoothDeviceNode* pPrevNode);
		CBluetoothDeviceNode* GetPreviousNode(void);

		bool SetBluetoothDeviceFind(HBLUETOOTH_DEVICE_FIND hBluetoothDeviceFind);
		HBLUETOOTH_DEVICE_FIND GetBluetoothDeviceFind(void);

		bool SetBluetoothDeviceInfo(BLUETOOTH_DEVICE_INFO BluetoothDeviceInfo);
		BLUETOOTH_DEVICE_INFO GetBluetoothDeviceInfo(void);

		wchar_t* GetBluetoothDeviceName(wchar_t* pszBuffer, int iSize);
		wchar_t* GetBluetoothDeviceAddress(wchar_t* pszBuffer, int iSize);
		unsigned long GetBluetoothDeviceClass(void);

	protected:

		CBluetoothDeviceNode* m_pNextNode;
		CBluetoothDeviceNode* m_pPrevNode;

		HBLUETOOTH_DEVICE_FIND m_hBluetoothDevice;
		BLUETOOTH_DEVICE_INFO m_BluetoothDeviceInfo;
};

#endif
