#include "usbEnum.hpp"

namespace liraEnumerator
{

usbEnum::usbEnum(const std::wstring &manufacture) :
	m_manufacture(manufacture)
{ }

usbEnum::~usbEnum(void)
{
	clear();
}

void usbEnum::clear()
{
	while (!USBDeviceDSCs.empty())
	{
		USBDeviceDSC *pdsc = USBDeviceDSCs.front();
		USBDeviceDSCs.pop_front();
		delete pdsc;
	} 
}

bool usbEnum::doScan()
{
	clear();
	doScan(m_manufacture);
	return (USBDeviceDSCs.size()>0);
}

void usbEnum::doScan(const std::wstring& manufacture)
{
    USBDeviceDSC * pdsc;
    typedef BOOL (WINAPI * FN_SetupDiGetDeviceProperty)(
        HDEVINFO DeviceInfoSet,
        PSP_DEVINFO_DATA DeviceInfoData,
        const DEVPROPKEY *PropertyKey,
        DEVPROPTYPE *PropertyType,
        PBYTE PropertyBuffer,
        DWORD PropertyBufferSize,
        PDWORD RequiredSize,
        DWORD Flags
    );

    FN_SetupDiGetDeviceProperty fn_SetupDiGetDeviceProperty;

#ifdef UNICODE
    fn_SetupDiGetDeviceProperty = (FN_SetupDiGetDeviceProperty)
        GetProcAddress (GetModuleHandle (TEXT("Setupapi.dll")), "SetupDiGetDevicePropertyW");
#else
    fn_SetupDiGetDeviceProperty = (FN_SetupDiGetDeviceProperty)
        GetProcAddress(GetModuleHandle(TEXT("Setupapi.dll")), "SetupDiGetDevicePropertyA");
#endif

    int result{0};
    HDEVINFO hwInfo{0};
    unsigned int i{0};
    const DEVPROPKEY DEVPKEY_Device_BusReportedDeviceDesc = {
        { 0x540b947e, 0x8b40, 0x45bc, {0xa8, 0xa2, 0x6a, 0x0b, 0x89, 0x4c, 0xbd, 0xa2} }, 4 };

    GUID myGUID_DEVCLASS_USB;
    myGUID_DEVCLASS_USB.Data1=0x36fc9e60L;
    myGUID_DEVCLASS_USB.Data2=0xc465;
    myGUID_DEVCLASS_USB.Data3=0x11cf;
    myGUID_DEVCLASS_USB.Data4[0]=0x80;
    myGUID_DEVCLASS_USB.Data4[1]=0x56;
    myGUID_DEVCLASS_USB.Data4[2]=0x44;
    myGUID_DEVCLASS_USB.Data4[3]=0x45;
    myGUID_DEVCLASS_USB.Data4[4]=0x53;
    myGUID_DEVCLASS_USB.Data4[5]=0x54;
    myGUID_DEVCLASS_USB.Data4[6]=0x00;
    myGUID_DEVCLASS_USB.Data4[7]=0x00;

    hwInfo = SetupDiGetClassDevs(&myGUID_DEVCLASS_USB, NULL, NULL, DIGCF_PRESENT);
    
    if (hwInfo != INVALID_HANDLE_VALUE) {
        i = 0;
        SP_DEVINFO_DATA devInfo;
        wchar_t tmpS[1024];
        
        devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
        for (;;) {
            if ( SetupDiEnumDeviceInfo(hwInfo, i, &devInfo) ) {
                i++;
                bool isLEMZDevice=false;
                if ( SetupDiGetDeviceRegistryProperty(hwInfo,
                        &devInfo,
                        SPDRP_MFG,
                        NULL,
                        (PBYTE)&tmpS, sizeof(tmpS), NULL) )
                {
                    ::std::cout << "Retrieved device manufacturer : " 
                                << tmpS << ::std::endl;
                    std::wstring s_tmp=tmpS;
                    isLEMZDevice = (s_tmp==manufacture);
                    if (!isLEMZDevice)
                    {
                        //may be new type of LIRA device
                        if (s_tmp==L"FTDI")
                        {
                            //ToDo
                            isLEMZDevice = true;
                        }
                    }
                }

                if (isLEMZDevice)
                {
                    pdsc = new USBDeviceDSC();

                    OSVERSIONINFOEX osvi;
                    memset(&osvi, 0, sizeof(OSVERSIONINFOEX));
                    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
                    DWORDLONG dwlConditionMask = 0;
                    int op=VER_GREATER_EQUAL;
                    osvi.dwMajorVersion = 10;
                    osvi.dwMinorVersion = 0;

                    VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, op );
                    VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );

                    if ( VerifyVersionInfo(&osvi,
                             VER_MAJORVERSION | VER_MINORVERSION,
                             dwlConditionMask) ) {
                            // On Vista and earlier, we can use only SPDRP_DEVICEDESC
                            // On Windows 7, the information we want ("Bus reported device description") is
                            // accessed through DEVPKEY_Device_BusReportedDeviceDesc
                           DWORD dwSize;
                           DEVPROPTYPE ulPropertyType;
                            if (fn_SetupDiGetDeviceProperty &&
                                    fn_SetupDiGetDeviceProperty (hwInfo,
                                                                 &devInfo,
                                                                 &DEVPKEY_Device_BusReportedDeviceDesc,
                                                                 &ulPropertyType,
                                                                 (PBYTE)&tmpS, sizeof(tmpS), &dwSize, 0))
                            {
                                pdsc->device_location=::std::wstring{ tmpS };
                                pdsc->device_location.replace(
                                    pdsc->device_location.begin(),
                                    pdsc->device_location.end(),
                                    " ", "_" );
                            }else
                            {
                                delete pdsc;
                                continue;
                            }
                    }else
                    {
                        if ( SetupDiGetDeviceRegistryProperty(hwInfo,
                                                            &devInfo,
                                                            SPDRP_LOCATION_INFORMATION,
                                                            NULL,
                                                            (PBYTE)&tmpS,sizeof(tmpS),NULL) )
                        {
                        ::std::cout << "Retrieved device hardware location : " 
                                    << tmpS << ::std::endl;
                                pdsc->device_location=::std::wstring{ tmpS };
                                pdsc->device_location.replace(
                                    pdsc->device_location.begin(),
                                    pdsc->device_location.end(),
                                    " ", "_" );
                        }else
                        {
                            delete pdsc;
                            continue;
                        }
                    }

                    if ( SetupDiGetDeviceRegistryProperty(hwInfo,
                                                        &devInfo,
                                                        SPDRP_HARDWAREID,
                                                        NULL,
                                                        (PBYTE)&tmpS, sizeof(tmpS), NULL) )
                    {
                        ::std::cout << "Retrieved device identification string : " 
                                    << tmpS << ::std::endl;
                        std::wstring s_tmp, s_tmp_upper;
                        s_tmp=tmpS;
                        ::std::transform(s_tmp.begin(),
                                       s_tmp.end(),
                                       ::std::back_inserter(s_tmp_upper),
                                       ::toupper);
                        s_tmp=s_tmp_upper;
                        //Find Product ID (PID)
                        std::string::size_type id=s_tmp.find(L"PID_");
                        if (id!=std::string::npos)
                        {
                            std::wstring s_hex=s_tmp.substr(id+4, 4);
                            pdsc->device_type = (liraUSBDevEnum) wcstol(s_hex.c_str(),NULL,16);
                        }
                        //Find Vendor ID (VID)
                        id=s_tmp.find(L"VID_");
                        if (id!=std::string::npos)
                        {
                            std::wstring s_hex=s_tmp.substr(id+4,4);
                            pdsc->device_vid = (unsigned short) wcstol(s_hex.c_str(),NULL,16);
                        }
                        //Find Product revision (REV)
                        id=s_tmp.find(L"REV_");
                        if (id!=std::string::npos)
                        {
                            std::wstring s_hex=s_tmp.substr(id+4,4);
                            pdsc->device_rev= (unsigned short) wcstol(s_hex.c_str(),NULL,16);
                        }
                    }else
                    {
                        delete pdsc;
                        continue;
                    }
                                                                                     
                    if ( SetupDiGetDeviceRegistryProperty(hwInfo,
                                                        &devInfo,
                                                        SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
                                                        NULL,
                                                        (PBYTE)&tmpS, sizeof(tmpS), NULL) )
                    {
                        ::std::cout << "Retrieved device PDO associated name : "
                                    << tmpS << ::std::endl;
                        std::wstring s_tmp = tmpS;
                        pdsc->device_name=::std::wstring{ L"\\\\?\\GLOBALROOT" } + s_tmp;
                    }else
                    {
                        delete pdsc;
                        continue;
                    }
                    
                    USBDeviceDSCs.push_back( pdsc );

                    if (GetLastError()) continue;
                }
            } else {
                result = GetLastError();
                if (result == ERROR_NO_MORE_ITEMS) result = 0;
                break;

            }
        }
        SetupDiDestroyDeviceInfoList(hwInfo);
    }
}

} //end namespace

/* EOF */