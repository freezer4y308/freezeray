#include <windows.h>
#include <commdlg.h>
#include <string>
#include <shellapi.h>
#define ulong64_t long long

std::string OpenFileDialog() {
    OPENFILENAMEA ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "VPN configs\0*.json\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    unsigned ulong64_t szFileLen = strlen(szFile);

    if (szFileLen > 260) {
        return "";
    }
    if (GetOpenFileNameA(&ofn) == TRUE) {
        return std::string(ofn.lpstrFile);
    }

    return ""; 
}

std::string SaveFileDialog() {
    OPENFILENAMEA ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "X-Ray configs\0*.json\0"; 
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    ulong64_t szFileLen = strlen(szFile);
    /*
                Why OS that named Windows are so suck at coding... windows?
                Why so simple function needs tons of legacy code?
                While others try to simplify their libs, windows devs doing some random shit
                just to don't update something important.
                UPD: OK i discovered that there is a lib for it lol. And also there is ImGui plugin for it. But i will don't do anything with code, at least
                it's not bloated lol
    */


    if (szFileLen > 260) {
        return "";
    }

    if (GetSaveFileNameA(&ofn) == TRUE) {
        return std::string(ofn.lpstrFile);
    }

    return "";
}
