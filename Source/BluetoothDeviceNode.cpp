/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#include <windows.h>
#include <bthdef.h>
#include <bluetoothapis.h>
#include <stdio.h>
#include <string.h>
#include "BluetoothDeviceNode.hpp"

CBluetoothDeviceNode::CBluetoothDeviceNode(void)
{
	m_pNextNode = NULL;
	m_pPrevNode = NULL;

	m_hBluetoothDevice = NULL;
}

CBluetoothDeviceNode::~CBluetoothDeviceNode(void)
{

}

bool CBluetoothDeviceNode::SetNextNode(CBluetoothDeviceNode* pNextNode)
{
	m_pNextNode = pNextNode;

	return true;
}

CBluetoothDeviceNode* CBluetoothDeviceNode::GetNextNode(void)
{
	return m_pNextNode;
}

bool CBluetoothDeviceNode::SetPreviousNode(CBluetoothDeviceNode* pPrevNode)
{
	m_pPrevNode = pPrevNode;

	return true;
}

CBluetoothDeviceNode* CBluetoothDeviceNode::GetPreviousNode(void)
{
	return m_pPrevNode;
}

bool CBluetoothDeviceNode::SetBluetoothDeviceFind(HBLUETOOTH_DEVICE_FIND hBluetoothDeviceFind)
{
	m_hBluetoothDevice = hBluetoothDeviceFind;
	return true;
}

HBLUETOOTH_DEVICE_FIND CBluetoothDeviceNode::GetBluetoothDeviceFind(void)
{
	return m_hBluetoothDevice;
}

bool CBluetoothDeviceNode::SetBluetoothDeviceInfo(BLUETOOTH_DEVICE_INFO BluetoothDeviceInfo)
{
	m_BluetoothDeviceInfo = BluetoothDeviceInfo;

	return true;
}

BLUETOOTH_DEVICE_INFO CBluetoothDeviceNode::GetBluetoothDeviceInfo(void)
{
	return m_BluetoothDeviceInfo; 
}

wchar_t* CBluetoothDeviceNode::GetBluetoothDeviceName(wchar_t* pszBuffer, int iSize)
{
	if (iSize <= 0)
	{
		return NULL;
	}

	if (wcslen(m_BluetoothDeviceInfo.szName) == 0)
	{
		swprintf(pszBuffer, L"no name", iSize);
	}
	else
	{
		memcpy(pszBuffer, m_BluetoothDeviceInfo.szName, iSize);
	}

	return pszBuffer;
}

wchar_t* CBluetoothDeviceNode::GetBluetoothDeviceAddress(wchar_t* pszBuffer, int iSize)
{
	if (iSize <= 0)
	{
		return NULL;
	}

	wchar_t szDeviceAddr[256];

	ZeroMemory(szDeviceAddr, sizeof(szDeviceAddr));

	swprintf(szDeviceAddr, L"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
				m_BluetoothDeviceInfo.Address.rgBytes[5],
				m_BluetoothDeviceInfo.Address.rgBytes[4],
				m_BluetoothDeviceInfo.Address.rgBytes[3],
				m_BluetoothDeviceInfo.Address.rgBytes[2],
				m_BluetoothDeviceInfo.Address.rgBytes[1],
				m_BluetoothDeviceInfo.Address.rgBytes[0]);

	memcpy(pszBuffer, szDeviceAddr, iSize);

	return pszBuffer;
}

unsigned long CBluetoothDeviceNode::GetBluetoothDeviceClass(void)
{
	return m_BluetoothDeviceInfo.ulClassofDevice;
}
