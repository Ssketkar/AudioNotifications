//this file is part of notepad++
//Copyright (C)2022 Don HO <don.h@free.fr>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma comment(lib, "winmm.lib")
#include "PluginDefinition.h"
#include <mmsystem.h>
#include <string>
#include <fstream>

extern FuncItem funcItem[nbFunc];
extern NppData nppData;
extern bool notifyOnSave;

BOOL APIENTRY DllMain(HANDLE hModule,DWORD  reasonForCall,LPVOID /*lpReserved*/)
{
	try {

		switch(reasonForCall)
		{
		case DLL_PROCESS_ATTACH:
			pluginInit(hModule);
			break;

		case DLL_PROCESS_DETACH:
			pluginCleanUp();
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
		}
	}
	catch(...) { return FALSE; }

	return TRUE;
}


extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR* getName()
{
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem* getFuncsArray(int* nbF)
{
	*nbF = nbFunc;
	return funcItem;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification* notifyCode)
{
	switch(notifyCode->nmhdr.code)
	{
	case NPPN_SHUTDOWN:
	{
		commandMenuCleanUp();
	}
	break;
	case NPPN_FILESAVED:
	{
		if(notifyOnSave)
		{
			LPCWSTR soundFile = L"C:\\Program Files\\Notepad++\\plugins\\AudioNotifications\\File_Saved.wav";
			if(!PlaySound(soundFile,NULL,SND_FILENAME | SND_ASYNC)) {
				MessageBox(NULL,TEXT("Failed to play sound!"),TEXT("Save Event Triggered"),MB_OK);
			}
		}
	}
	break;

	default:
		return;
	}
}


// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// https://github.com/notepad-plus-plus/notepad-plus-plus/issues
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT /*Message*/,WPARAM /*wParam*/,LPARAM /*lParam*/)
{
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return TRUE;
}
#endif //UNICODE
