/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#ifndef _BLUETOOTHDEVICELIST_HEADER_
#define _BLUETOOTHDEVICELIST_HEADER_

#include "BluetoothDeviceNode.hpp"

class CBluetoothDeviceList
{
	public:

		CBluetoothDeviceList(void);
		~CBluetoothDeviceList(void);

		bool SetHeadNode(CBluetoothDeviceNode* pNewHeadNode);
		CBluetoothDeviceNode* GetHeadNode(void);

		bool SetTailNode(CBluetoothDeviceNode* pNewTailNode);
		CBluetoothDeviceNode* GetTailNode(void);

		bool AddBluetoothDeviceToList(HBLUETOOTH_DEVICE_FIND hBluetoothDevice, BLUETOOTH_DEVICE_INFO* pBluetoothDeviceInfo);
		CBluetoothDeviceNode* GetBluetoothDeviceFromList(int iNodeIndex);

		bool DeleteBluetoothDeviceFromList(CBluetoothDeviceNode* pBluetoothDeviceNode);

		int GetTotalBluetoothDevices(void);

	protected:

		CBluetoothDeviceNode* m_pHeadNode;
		CBluetoothDeviceNode* m_pTailNode;

		int m_iBluetoothDeviceCount;
};

#endif
