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

#include <Windows.h>
#include "PluginDefinition.h"
#include "menuCmdID.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

bool notifyOnSave;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
    notifyOnSave = true;
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp() {
}

// This function is called every time a file is saved in Notepad++
void onFileSave() {
    // Example action: display a message or modify the document.
    notifyOnSave = !notifyOnSave;
    ::CheckMenuItem(::GetMenu(nppData._nppHandle),funcItem[AUDIO_NOTIFICATIONS_SAVE_FILE]._cmdID,MF_BYCOMMAND | (notifyOnSave ? MF_CHECKED : MF_UNCHECKED));
    if(notifyOnSave)
    {
        MessageBox(NULL,TEXT("File save audio notification is enabled!"),TEXT("Save Event Triggered"),MB_OK);
    }
    // Additional actions can be performed here, such as:
    // - Logging the save event
    // - Modifying the document's content
    // - Performing automated backups, etc.
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(AUDIO_NOTIFICATIONS_SAVE_FILE,TEXT("On Save"),onFileSave,NULL,true);
    //setCommand(1, TEXT("Hello (with dialog)"), helloDlg, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
    // Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index,TCHAR* cmdName,PFUNCPLUGINCMD pFunc,ShortcutKey* sk,bool check0nInit)
{
    if(index >= nbFunc)
        return false;

    if(!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName,cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}
