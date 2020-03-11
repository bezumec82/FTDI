#include <windows.h>
#include <ftd2xx.h>
#include <iostream>

int main( int , char** )
{
    FT_STATUS ft_status;
    FT_DEVICE_LIST_INFO_NODE * dev_info = NULL;
    DWORD num_devs;

    // create the device information list 
    ft_status = FT_CreateDeviceInfoList(&num_devs);

    dev_info = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*num_devs);

    ft_status = FT_GetDeviceInfoList(dev_info, &num_devs);

    /*
    typedef struct _ft_device_list_info_node {
        ULONG Flags;
        ULONG Type;
        ULONG ID;
        DWORD LocId;
        char SerialNumber[16];
        char Description[64];
        FT_HANDLE ftHandle;
    } FT_DEVICE_LIST_INFO_NODE;
    */
    if( ft_status == FT_OK )
    {
        if( ! num_devs ) { ::std::cout << "No devices in system" << ::std::endl; }
        else
        {
            for( int dev_idx = 0; dev_idx < num_devs; dev_idx++ )
            {
                ::std::cout << "Flags        : "     << dev_info[dev_idx].Flags          << '\n'
                            << "Type         : "     << dev_info[dev_idx].Type           << '\n'
                            << "ID           : "     << dev_info[dev_idx].ID             << '\n'
                            << "LocId        : "     << dev_info[dev_idx].LocId          << '\n'
                            << "SerialNumber : "     << dev_info[dev_idx].SerialNumber   << '\n'
                            << "Description  : "     << dev_info[dev_idx].Description    << '\n'
                            << "Type         : "     << dev_info[dev_idx].Type           << '\n'
                            << ::std::endl;
                /* READING */
                char RxBuffer[256];
                DWORD RxBytes;
                DWORD TxBytes;
                DWORD EventDWord;
                DWORD BytesReceived;
                ft_status = FT_Open(dev_idx, &dev_info[dev_idx].ftHandle);
                if( ft_status != FT_OK )
                {
                    ::std::cout << "Can't open device # " << dev_idx << ::std::endl;
                }
                
                FT_GetStatus( dev_info[dev_idx].ftHandle, &RxBytes, &TxBytes, &EventDWord );
                if (RxBytes > 0) 
                {
                    if( RxBytes > sizeof( RxBuffer ) ) RxBytes = sizeof( RxBuffer );

                    ft_status = FT_Read( dev_info[dev_idx].ftHandle, RxBuffer, RxBytes, &BytesReceived);
                    if (ft_status == FT_OK) 
                    {
                        ::std::cout << ::std::hex << RxBuffer << ::std::endl;
                    }
                }
                else
                {
                    ::std::cout << "Buffer empty" << ::std::endl;
                }
                FT_Close( dev_info[dev_idx].ftHandle );

            }


        }
    }
    else
    {
        ::std::cout << "Error code : " << ft_status << ::std::endl;
    }
    
    return int(ft_status);
}