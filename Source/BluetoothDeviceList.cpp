/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#include "BluetoothDeviceList.hpp"
#include "BluetoothDeviceNode.hpp"

/*------------------------------------------------------------
*  Constructor
*  Initialise members to default values.
*------------------------------------------------------------*/
CBluetoothDeviceList::CBluetoothDeviceList(void)
{
	m_pHeadNode = NULL;
	m_pTailNode = NULL;
	m_iBluetoothDeviceCount = 0;
}

/*------------------------------------------------------------
*  Destructor
*  Clean up any dynamically allocated memory.
*------------------------------------------------------------*/
CBluetoothDeviceList::~CBluetoothDeviceList(void)
{
	CBluetoothDeviceNode* pCurrNode = this->GetHeadNode();
	CBluetoothDeviceNode* pNextNode = NULL;

	for (int iNodeIndex = 0; iNodeIndex < this->GetTotalBluetoothDevices(); iNodeIndex++)
	{
		pNextNode = pCurrNode->GetNextNode();

		delete pCurrNode;

		pCurrNode = pNextNode;
	}
}

/*------------------------------------------------------------
*  SetHeadNode()
*  Set the head node of the linked list.
*------------------------------------------------------------*/
bool CBluetoothDeviceList::SetHeadNode(CBluetoothDeviceNode* pNewHeadNode)
{
	m_pHeadNode = pNewHeadNode;
	return true;
}

/*------------------------------------------------------------
*  GetHeadNode()
*  Get the head node of the linked list.
*------------------------------------------------------------*/
CBluetoothDeviceNode* CBluetoothDeviceList::GetHeadNode(void)
{
	return m_pHeadNode;
}

/*------------------------------------------------------------
*  SetTailNode()
*  Set the tail node of the linked list.
*------------------------------------------------------------*/
bool CBluetoothDeviceList::SetTailNode(CBluetoothDeviceNode* pNewTailNode)
{
	m_pTailNode = pNewTailNode;
	return true;
}

/*------------------------------------------------------------
*  GetTailNode()
*  Get the tail node of the linked list.
*------------------------------------------------------------*/
CBluetoothDeviceNode* CBluetoothDeviceList::GetTailNode(void)
{
	return m_pTailNode;
}

/*------------------------------------------------------------
*  AddBluetoothDeviceToList()
*  Add a new Bluetooth device to the linked list.
*------------------------------------------------------------*/
bool CBluetoothDeviceList::AddBluetoothDeviceToList(HBLUETOOTH_DEVICE_FIND hBluetoothDevice, BLUETOOTH_DEVICE_INFO* pBluetoothDeviceInfo)
{
	CBluetoothDeviceNode* pNewBluetoothDevice = new CBluetoothDeviceNode();

	pNewBluetoothDevice->SetBluetoothDeviceInfo(*pBluetoothDeviceInfo);


	if (this->GetTotalBluetoothDevices() == 0)
	{
		pNewBluetoothDevice->SetNextNode(NULL);
		pNewBluetoothDevice->SetPreviousNode(NULL);

		this->SetHeadNode(pNewBluetoothDevice);
		this->SetTailNode(pNewBluetoothDevice);
	}
	else
	{
		pNewBluetoothDevice->SetNextNode(NULL);
		pNewBluetoothDevice->SetPreviousNode(this->GetTailNode());

		this->GetTailNode()->SetNextNode(pNewBluetoothDevice);
		this->SetTailNode(pNewBluetoothDevice);
	}

	m_iBluetoothDeviceCount++;

	return true;
}

/*------------------------------------------------------------
*  GetBluetoothDeviceFromList()
*  Get a Bluetooth device from the linked list.
*------------------------------------------------------------*/
CBluetoothDeviceNode* CBluetoothDeviceList::GetBluetoothDeviceFromList(int iDeviceNodeIndex)
{
	if (iDeviceNodeIndex <= 0)
	{
		return NULL;
	}

	CBluetoothDeviceNode* pCurrNode = this->GetHeadNode();

	for (int iNodeIndex = 0; iNodeIndex < this->GetTotalBluetoothDevices(); iNodeIndex++)
	{
		if (iDeviceNodeIndex == iNodeIndex)
		{
			return pCurrNode;
		}

		pCurrNode = pCurrNode->GetNextNode();
	}

	return NULL;
}

/*------------------------------------------------------------
*  GetTotalBluetoothDevices()
*  Get the total Bluetooth devices in the linked list.
*------------------------------------------------------------*/
int CBluetoothDeviceList::GetTotalBluetoothDevices(void)
{
	return m_iBluetoothDeviceCount;
}
