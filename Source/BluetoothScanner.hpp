/*------------------------------------------------------------
*  Bluetooth device scanner (C) 2007 - Tom Bell
*  http://tombell.org.uk
*------------------------------------------------------------*/
#ifndef _BLUETOOTHSCANNER_HEADER_
#define _BLUETOOTHSCANNER_HEADER_

/*------------------------------------------------------------
*  Link with the irprops static library.
*------------------------------------------------------------*/
#pragma comment(lib, "irprops.lib")

/*------------------------------------------------------------
*  Define constants for ASCII characters.
*------------------------------------------------------------*/
#define LINK_CHARACTER_MIDDLE 195
#define LINK_CHARACTER_END    192

/*------------------------------------------------------------
*  Function prototypes.
*------------------------------------------------------------*/
void PrintLogo(void);
bool FindBluetoothDevices(CBluetoothDeviceList* pBluetoothDeviceList);
wchar_t* GetMajorDeviceClass(unsigned long ulClassOfDevice, wchar_t* pszBuffer, int iSize);
wchar_t* GetMinorDeviceClass(unsigned long ulClassOfDevice, wchar_t* pszBuffer, int iSize);
bool DisplayBluetoothDeviceInformation(CBluetoothDeviceList* pBluetoothDeviceList);

#endif
