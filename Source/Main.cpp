/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#include <windows.h>
#include <bthdef.h>
#include <bluetoothapis.h>
#include <stdio.h>

#include "BluetoothDeviceList.hpp"
#include "BluetoothDeviceNode.hpp"
#include "BluetoothScanner.hpp"

/*------------------------------------------------------------
*  PrintLogo()
*  Display the application logo.
*------------------------------------------------------------*/
void PrintLogo(void)
{
	wprintf(L"Bluetooth Device Scanner (C) 2007 Tom Bell\n");
	wprintf(L"http://www.ownthebox.net\n\n");
}

/*------------------------------------------------------------
*  FindBluetoothDevices()
*  Find a list of bluetooth devices.
*------------------------------------------------------------*/
bool FindBluetoothDevices(CBluetoothDeviceList* pBluetoothDeviceList)
{
	BLUETOOTH_DEVICE_SEARCH_PARAMS BluetoothSearchParams;
	BLUETOOTH_DEVICE_INFO BluetoothDeviceInfo;
	HBLUETOOTH_DEVICE_FIND hBluetoothDevice;

	ZeroMemory(&BluetoothDeviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));
	ZeroMemory(&BluetoothSearchParams, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));

	BluetoothDeviceInfo.dwSize = sizeof(BluetoothDeviceInfo);

	BluetoothSearchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
	BluetoothSearchParams.fReturnAuthenticated= true;
	BluetoothSearchParams.fReturnRemembered = true;
	BluetoothSearchParams.fReturnUnknown = true;
	BluetoothSearchParams.fReturnConnected = true;
	BluetoothSearchParams.fIssueInquiry = true;
	BluetoothSearchParams.cTimeoutMultiplier = 20;
	BluetoothSearchParams.hRadio = NULL;

	hBluetoothDevice = BluetoothFindFirstDevice(&BluetoothSearchParams, &BluetoothDeviceInfo);

	if (hBluetoothDevice != NULL)
	{
		while (true)
		{
			pBluetoothDeviceList->AddBluetoothDeviceToList(hBluetoothDevice, &BluetoothDeviceInfo);

			if (BluetoothFindNextDevice(hBluetoothDevice, &BluetoothDeviceInfo) == false)
			{
				break;
			}
		}

		BluetoothFindDeviceClose(hBluetoothDevice);

		return true;
	}

	return false;
}

/*------------------------------------------------------------
*  GetMajorDeviceClass()
*  Get the major device class of the Bluetooth device as a
*  string.
*------------------------------------------------------------*/
wchar_t* GetMajorDeviceClass(unsigned long ulClassOfDevice, wchar_t* pszBuffer, int iSize)
{
	if (iSize <= 0)
	{
		return NULL;
	}

	wchar_t* pszMajorDeviceClass[] =
	{
		L"Miscellaneous",
		L"Computer",
		L"Phone",
		L"LAN Access",
		L"Audio/Video",
		L"Peripheral",
		L"Imaging",
		L"Wearable",
		L"Toy"
	};

	unsigned char szMajorDeviceClass = (unsigned char) ((ulClassOfDevice & 0x0000ff00) >> 8);

	memcpy(pszBuffer, pszMajorDeviceClass[szMajorDeviceClass & 0x0f], iSize);

	return pszBuffer;
}

/*------------------------------------------------------------
*  GetMinorDeviceClass()
*  Get the minor device class of the Bluetooth device as a
*  string.
*------------------------------------------------------------*/
wchar_t* GetMinorDeviceClass(unsigned long ulClassOfDevice, wchar_t* pszBuffer, int iSize)
{
	if (iSize <= 0)
	{
		return NULL;
	}

	unsigned char szMajorDeviceClass = (unsigned char) (((ulClassOfDevice & 0x00ff00) >> 8));
	unsigned char szMinorDeviceClass = (unsigned char) (((ulClassOfDevice & 0x0000ff)));

	switch (szMajorDeviceClass & 0x0f)
	{
		case 0:
			memcpy(pszBuffer, L"None", iSize);
		break;

		case 1:
			switch ((szMinorDeviceClass & 0x0f) >> 2)
			{
				case 0:
					memcpy(pszBuffer, L"Uncategorised", iSize);
				break;

				case 1:
					memcpy(pszBuffer, L"Desktop", iSize);
				break;

				case 2:
					memcpy(pszBuffer, L"Server", iSize);
				break;
				
				case 3:
					memcpy(pszBuffer, L"Laptop", iSize);
				break;
				
				case 4:
					memcpy(pszBuffer, L"Handheld", iSize);
				break;
				
				case 5:
					memcpy(pszBuffer, L"Palm", iSize);
				break;
				
				case 6:
					memcpy(pszBuffer, L"Wearable", iSize);
				break;
			}
		break;

		case 2:
			switch ((szMinorDeviceClass & 0x0f) >> 2)
			{
				case 0:
					memcpy(pszBuffer, L"Uncategorised", iSize);
				break;

				case 1:
					memcpy(pszBuffer, L"Mobile", iSize);
				break;

				case 2:
					memcpy(pszBuffer, L"Cordless", iSize);
				break;
				
				case 3:
					memcpy(pszBuffer, L"Smart phone", iSize);
				break;
				
				case 4:
					memcpy(pszBuffer, L"Wired modem or voice gateway", iSize);
				break;
				
				case 5:
					memcpy(pszBuffer, L"Common ISDN access", iSize);
				break;
				
				case 6:
					memcpy(pszBuffer, L"Sim card reader", iSize);
				break;
			}
		break;

		case 3:
			if (((szMinorDeviceClass & 0x0f) >> 2) == 0)
			{
				memcpy(pszBuffer, L"Uncategorised", iSize);
			}

			switch (((szMinorDeviceClass & 0x0f) >> 2) / 8)
			{
				case 0:
					memcpy(pszBuffer, L"Fully available", iSize);
				break;
				
				case 1:
					memcpy(pszBuffer, L"1-17%% available", iSize);
				break;
				
				case 2:
					memcpy(pszBuffer, L"17-33%% utilised", iSize);
				break;
				
				case 3:
					memcpy(pszBuffer, L"33-50%% utilised", iSize);
				break;
				
				case 4:
					memcpy(pszBuffer, L"50-67%% utilised", iSize);
				break;
				
				case 5:
					memcpy(pszBuffer, L"67-83%% utilised", iSize);
				break;
				
				case 6:
					memcpy(pszBuffer, L"83-99%% utilised", iSize);
				break;
				
				case 7:
					memcpy(pszBuffer, L"No service available", iSize);
				break;
			}
		break;

		case 4:
			switch ((szMinorDeviceClass & 0x0f) >> 2)
			{
				case 0:
					memcpy(pszBuffer, L"Uncategorised", iSize);
				break;

				case 1:
					memcpy(pszBuffer, L"Device conforms to the Headset profile", iSize);
				break;

				case 2:
					memcpy(pszBuffer, L"Hands-free", iSize);
				break;

				case 3:
					memcpy(pszBuffer, L"Reserved", iSize);
				break;

				case 4:
					memcpy(pszBuffer, L"Microphone", iSize);
				break;

				case 5:
					memcpy(pszBuffer, L"Loudspeaker", iSize);
				break;

				case 6:
					memcpy(pszBuffer, L"Headphones", iSize);
				break;

				case 7:
					memcpy(pszBuffer, L"Portable audio", iSize);
				break;

				case 8:
					memcpy(pszBuffer, L"Car audio", iSize);
				break;

				case 9:
					memcpy(pszBuffer, L"Set-top box", iSize);
				break;

				case 10:
					memcpy(pszBuffer, L"HiFi audio device", iSize);
				break;

				case 11:
					memcpy(pszBuffer, L"VCR", iSize);
				break;

				case 12:
					memcpy(pszBuffer, L"Video camera", iSize);
				break;

				case 13:
					memcpy(pszBuffer, L"Camcorder", iSize);
				break;

				case 14:
					memcpy(pszBuffer, L"Video monitor", iSize);
				break;

				case 15:
					memcpy(pszBuffer, L"Video display and loudspeaker", iSize);
				break;

				case 16:
					memcpy(pszBuffer, L"Video conferencing", iSize);
				break;

				case 17:
					memcpy(pszBuffer, L"Reserved", iSize);
				break;

				case 18:
					memcpy(pszBuffer, L"Gaming/toy", iSize);
				break;
			}
		break;

		case 5:
			switch (((szMinorDeviceClass & 0x0f) >> 2) & 48)
			{
				case 16:
					memcpy(pszBuffer, L"Keyboard", iSize);
				break;

				case 32:
					memcpy(pszBuffer, L"Pointing device", iSize);
				break;

				case 48:
					memcpy(pszBuffer, L"Combo keyboard/pointing device", iSize);
			}

			wcscat(pszBuffer, L" - ");

			switch (((szMinorDeviceClass & 0x0f) >> 2) & 15)
			{
				case 1:
					wcsncat(pszBuffer, L"Joystick", iSize - wcslen(pszBuffer));
				break;

				case 2:
					wcsncat(pszBuffer, L"Gamepad", iSize - wcslen(pszBuffer));
				break;
				
				case 3:
					wcsncat(pszBuffer, L"Remote control", iSize - wcslen(pszBuffer));
				break;
				
				case 4:
					wcsncat(pszBuffer, L"Sensing device", iSize - wcslen(pszBuffer));
				break;
				
				case 5:
					wcsncat(pszBuffer, L"Digitiser tablet", iSize - wcslen(pszBuffer));
				break;
				
				case 6:
					wcsncat(pszBuffer, L"Card reader", iSize - wcslen(pszBuffer));
				break;
				
				default:
					wcsncat(pszBuffer, L"Reserved", iSize - wcslen(pszBuffer));
				break;
			}
		break;

		case 6:
			if (((szMinorDeviceClass & 0x0f) >> 2) & 4)
			{
				memcpy(pszBuffer, L"Display", iSize);
			}
			else if (((szMinorDeviceClass & 0x0f) >> 2) & 8)
			{
				memcpy(pszBuffer, L"Camera", iSize);
			}
			else if (((szMinorDeviceClass & 0x0f) >> 2) & 16)
			{
				memcpy(pszBuffer, L"Scanner", iSize);
			}
			else if (((szMinorDeviceClass & 0x0f) >> 2) & 32)
			{
				memcpy(pszBuffer, L"Printer", iSize);
			}
		break;

		case 7:
			switch ((szMinorDeviceClass & 0x0f) >> 2)
			{
				case 1:
					memcpy(pszBuffer, L"Wrist watch", iSize);
				break;

				case 2:
					memcpy(pszBuffer, L"Pager", iSize);
				break;

				case 3:
					memcpy(pszBuffer, L"Jacket", iSize);
				break;

				case 4:
					memcpy(pszBuffer, L"Helmet", iSize);
				break;
			
				case 5:
					memcpy(pszBuffer, L"Glasses", iSize);
				break;
			}
		break;
		
		case 8:
			switch ((szMinorDeviceClass & 0x0f) >> 2)
			{
				case 1:
					memcpy(pszBuffer, L"Robot", iSize);
				break;

				case 2:
					memcpy(pszBuffer, L"Vehicle", iSize);
				break;

				case 3:
					memcpy(pszBuffer, L"Doll/action figure", iSize);
				break;
				
				case 4:
					memcpy(pszBuffer, L"Controller", iSize);
				break;
				
				case 5:
					memcpy(pszBuffer, L"Game", iSize);
				break;
			}
		break;
	}

	return pszBuffer;
}

/*------------------------------------------------------------
*  DisplayBluetoothDeviceInformation()
*  Display information about each Bluetooth device found.
*------------------------------------------------------------*/
bool DisplayBluetoothDeviceInformation(CBluetoothDeviceList* pBluetoothDeviceList)
{
	if (pBluetoothDeviceList->GetTotalBluetoothDevices() == 0)
	{
		return false;
	}

	CBluetoothDeviceNode* pCurrDeviceNode = pBluetoothDeviceList->GetHeadNode();

	for (int iCurrNodeIndex = 0; iCurrNodeIndex < pBluetoothDeviceList->GetTotalBluetoothDevices(); iCurrNodeIndex++)
	{
		wchar_t szDeviceName[256];
		wchar_t szDeviceAddr[256];
		wchar_t szMajorDeviceClass[256];
		wchar_t szMinorDeviceClass[256];

		ZeroMemory(szDeviceName, sizeof(szDeviceName));
		ZeroMemory(szDeviceAddr, sizeof(szDeviceAddr));
		ZeroMemory(szMajorDeviceClass, sizeof(szMajorDeviceClass));
		ZeroMemory(szMinorDeviceClass, sizeof(szMinorDeviceClass));

		pCurrDeviceNode->GetBluetoothDeviceName(szDeviceName, 256);
		pCurrDeviceNode->GetBluetoothDeviceAddress(szDeviceAddr, 256);

		GetMajorDeviceClass(pCurrDeviceNode->GetBluetoothDeviceClass(), szMajorDeviceClass, 256);
		GetMinorDeviceClass(pCurrDeviceNode->GetBluetoothDeviceClass(), szMinorDeviceClass, 256);

		wprintf(L"* Device information\n");
		wprintf(L"%c Device name:        %s\n", LINK_CHARACTER_MIDDLE, szDeviceName);
		wprintf(L"%c Device address:     %s\n", LINK_CHARACTER_MIDDLE, szDeviceAddr);
		wprintf(L"%c Device major class: %s\n", LINK_CHARACTER_MIDDLE, szMajorDeviceClass);
		wprintf(L"%c Device minor class: %s\n", LINK_CHARACTER_END,    szMinorDeviceClass);

		wprintf(L"\n");

		pCurrDeviceNode = pCurrDeviceNode->GetNextNode();
	}

	return true;
}

/*------------------------------------------------------------
*  main()
*  Main application entry point.
*------------------------------------------------------------*/
int wmain(int argc, wchar_t** argv)
{
	PrintLogo();

	CBluetoothDeviceList* pBluetoothDeviceList = new CBluetoothDeviceList();

	if (FindBluetoothDevices(pBluetoothDeviceList))
	{
		DisplayBluetoothDeviceInformation(pBluetoothDeviceList);

		if (pBluetoothDeviceList->GetTotalBluetoothDevices() == 1)
		{
			wprintf(L"Found %d device.\n", pBluetoothDeviceList->GetTotalBluetoothDevices());
		}
		else
		{
			wprintf(L"Found %d devices.\n", pBluetoothDeviceList->GetTotalBluetoothDevices());
		}
		
	}
	else
	{
		wprintf(L"Unable to find any bluetooth devices.\n");
	}

	delete pBluetoothDeviceList;

	return 0;
}
