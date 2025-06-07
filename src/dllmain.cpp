#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "constants.h"
#include "Methods.h"

void hook() {
    std::cout << "[+] Hook Initialized - Press any key to exit.\n";
}

// Global flag to control aimbot state
bool g_aimbotActive = false;
// Global handle for the aimbot thread
HANDLE hAimbotThread = nullptr;

DWORD WINAPI AimbotThread(LPVOID lpParam) {
    Methods* methods = static_cast<Methods*>(lpParam); // Cast the LPVOID to Methods*
    while (g_aimbotActive) {
        methods->aimbot(); // Call your aimbot logic
        Sleep(1); // Small delay to prevent 100% CPU usage, adjust as needed
    }
    return 0;
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
        if (input == "god") godFlag = methods.godMode(godFlag);
        if (input == "ammo") ammoFlag = methods.patchAmmo(ammoFlag);
        if (input == "help") {
            std::cout << "exit \n god \n ammo \n help" << std::endl;
        }
        if (input == "debug") {
            std::cout << "Debugging is not implemented yet." << std::endl;
		}
		if (input == "name") methods.printPlayerName();
        if (input == "aim") {
            if (!g_aimbotActive) {
                g_aimbotActive = true;
                hAimbotThread = CreateThread(nullptr, 0, AimbotThread, &methods, 0, nullptr);
                std::cout << "[+] Aimbot ON\n";
            }
            else {
                g_aimbotActive = false;
                if (hAimbotThread) {
                    WaitForSingleObject(hAimbotThread, INFINITE);
                    CloseHandle(hAimbotThread);
                    hAimbotThread = nullptr;
                }
                std::cout << "[-] Aimbot OFF\n";
            }
        }
		if (input == "enemy") methods.enemy();
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
