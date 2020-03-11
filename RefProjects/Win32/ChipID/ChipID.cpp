// ChipID.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "Resource.h"
#include "FTChipID.h"

//---------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK ChipIDDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_CHIPID),
	          hWnd, reinterpret_cast<DLGPROC>(ChipIDDlgProc));

	return FALSE;
}
//--------------------------------------------------------------------------
void InsertDevNumberItem(HWND hList, LVITEM * plvItem, int iDevNumber)
{
	char cDevNumber[10];
		
	sprintf(cDevNumber, "%d", iDevNumber);
	plvItem->mask = LVIF_TEXT;
	plvItem->cchTextMax = 256;
 	plvItem->iItem = iDevNumber;              
	plvItem->iSubItem = 0;         
	plvItem->pszText = cDevNumber;   
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)plvItem);

}
//--------------------------------------------------------------------------
void InsertSubItem(HWND hList, LVITEM * plvItem, int iIndex, char * cSubItemText)
{
	plvItem->pszText = cSubItemText;
    plvItem->iSubItem = iIndex;
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)plvItem);
}
//--------------------------------------------------------------------------
void PopulateListView(HWND hWndDlg, HWND hList)
{
	FTID_STATUS dStatus;
	unsigned long ulNumDevices, ulLocID, ulChipID;
	char cSerialNumber[50], cDescription[100], cLocationIDS[10], cChipIDS[10], ErrorMessage[256];
	LVITEM lvItem;

	if(hList == NULL) {
		hList = GetDlgItem(hWndDlg, IDC_DEVICE_LIST);
	}

	SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);

	dStatus = FTID_GetNumDevices(&ulNumDevices);

	if((dStatus == FTID_SUCCESS) && ulNumDevices) {

		for(int i = 0; i < (int)ulNumDevices; i++) {
			InsertDevNumberItem(hList, &lvItem, i);

			dStatus = FTID_GetDeviceSerialNumber(i, cSerialNumber, 50);
			if(dStatus == FTID_SUCCESS) {
				InsertSubItem(hList, &lvItem, 1, cSerialNumber);
			}

			dStatus = FTID_GetDeviceDescription(i, cDescription, 100);
			if(dStatus == FTID_SUCCESS) {
				InsertSubItem(hList, &lvItem, 2, cDescription);
			}

			dStatus = FTID_GetDeviceLocationID(i, &ulLocID);
			if(dStatus == FTID_SUCCESS) {
				sprintf(cLocationIDS, "0x%08X", ulLocID);
				InsertSubItem(hList, &lvItem, 3, cLocationIDS);
			}

			dStatus = FTID_GetDeviceChipID(i, &ulChipID);
			if(dStatus == FTID_SUCCESS) {
				sprintf(cChipIDS, "0x%08X", ulChipID);
				InsertSubItem(hList, &lvItem, 4, cChipIDS);
			}
		}
	}

	if(dStatus != FTID_SUCCESS) {
		FTID_GetErrorCodeString("EN", dStatus, ErrorMessage, 256);
		MessageBox(hWndDlg, ErrorMessage, NULL, MB_OK);
	}
}
//---------------------------------------------------------------------------
LRESULT CALLBACK ChipIDDlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HWND hWndOwner, hList = NULL; 
	RECT rc, rcDlg, rcOwner; 
	LVCOLUMN lvCol; 

	switch(Msg)
	{
	case WM_INITDIALOG:

		InitCommonControls();

		hList = GetDlgItem(hWndDlg, IDC_DEVICE_LIST);

		memset(&lvCol,0,sizeof(lvCol));
		lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM; 
		lvCol.cx = 0x1E;
		lvCol.pszText = "Number";                          

		SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol); 
		lvCol.cx = 0x50;
		lvCol.pszText = "Serial";                       
		SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol); 
		lvCol.cx = 0x64;
		lvCol.pszText = "Description";                              
		SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&lvCol); 
		lvCol.cx = 0x4D;
		lvCol.pszText = "LocationID";                            
		SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&lvCol); 
		lvCol.cx = 0x64;
		lvCol.pszText = "ChipID";                      
		SendMessage(hList, LVM_INSERTCOLUMN, 4, (LPARAM)&lvCol);

		// taken from msdn
        if ((hWndOwner = GetParent(hWndDlg)) == NULL) 
        {
            hWndOwner = GetDesktopWindow(); 
        }

        GetWindowRect(hWndOwner, &rcOwner); 
        GetWindowRect(hWndDlg, &rcDlg); 
        CopyRect(&rc, &rcOwner); 
 
         // Offset the owner and dialog box rectangles so that 
         // right and bottom values represent the width and 
         // height, and then offset the owner again to discard 
         // space taken up by the dialog box. 
 
        OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); 
        OffsetRect(&rc, -rc.left, -rc.top); 
        OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom); 
 
         // The new position is the sum of half the remaining 
         // space and the owner's original position. 
 
        SetWindowPos(hWndDlg, 
            HWND_BOTTOM, 
            rcOwner.left + (rc.right / 2), 
            rcOwner.top + (rc.bottom / 2), 
            0, 0,          // ignores size arguments 
            SWP_NOSIZE); 
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDC_FIND_DEVICES:
			PopulateListView(hWndDlg, hList);
			break;

		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//---------------------------------------------------------------------------




