#include <Windows.h>
#include <iostream>
#include <conio.h> // For _getch()
#include "genCode.h"
#include "constants.h"
#include "Methods.h"

void hook() {
    std::cout << "[+] Hook Initialized - Press any key to exit.\n";
}


void console() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    bool ammoFlag = false;
    bool godFlag = false;
    std::cout << "[+] Console Initialized\n";

    Methods methods;

    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "exit") break;
        if (input == "up") localPlayerPtr->PlayerFeetPos.y += 5;
        if (input == "down") localPlayerPtr->PlayerFeetPos.y -= 5;
        if (input == "print") std::cout << "Local Player Ptr: " << localPlayerPtr << std::endl;
        if (input == "god") godFlag = methods.godMode(godFlag);
        if (input == "ammo") ammoFlag = methods.patchAmmo(ammoFlag);
    }
    FreeConsole();
    ExitThread(0);
}


HANDLE hConsoleThread, hHookThread;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        hConsoleThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        hHookThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        FreeConsole();
        if (hConsoleThread) CloseHandle(hConsoleThread);
        if (hHookThread) CloseHandle(hHookThread);
        break;
    }
    return TRUE;
}
