#ifndef __USB_ENUM_HPP__
#define __USB_ENUM_HPP__

#include <string>
#include <list>
#include <algorithm>
#include <iostream>

#include <windows.h>
#include <SetupAPI.h>

namespace liraEnumerator
{

    enum liraUSBDevEnum
    {
        ptt         = 0x8003,
        speaker     = 0x8004,
        microphone  = 0x8008,
        headset     = 0x8009,
        iline       = 0x800d,
        tmicrophone = 0x800e,
        handset     = 0x800f,
        control     = 0x8020,
        controlEx   = 0x6001
    };

    struct USBDeviceDSC
    {
        ::std::wstring  device_name;
        ::std::wstring  device_location;
        liraUSBDevEnum  device_type;
        unsigned short  device_vid;
        unsigned short  device_rev;
    };

    class usbEnum
    {
    public : /*--- Constructors ---*/
        usbEnum(const std::wstring& );

    public : /*--- Destructors ---*/
        virtual ~usbEnum();

    public : /*--- Methods ---*/
        bool doScan();
        USBDeviceDSC * Find(const liraUSBDevEnum devType);
        USBDeviceDSC * Find(const ::std::string &devLocation);
    private :
        void doScan(const std::wstring &manufacture);
        void clear();

    public : /*--- Variables ---*/
        ::std::list <USBDeviceDSC *> USBDeviceDSCs;
    private :
         std::wstring m_manufacture;
    };

}

#endif