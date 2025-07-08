#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "constants.h"
#include "Methods.h"

// Global Methods instance shared across threads
Methods g_methods;

// Global flags and handles
bool g_aimbotActive = false;
HANDLE hAimbotThread = nullptr;

bool g_espActive = false;
HANDLE hEspThread = nullptr;

bool g_godMode = false;
HANDLE hGodThread = nullptr;


bool g_triggerBot = false;
HANDLE hTriggerThread = nullptr;

DWORD WINAPI TriggerThread(LPVOID) {
    while (g_triggerBot) {
        g_methods.triggerBot(g_triggerBot);
        Sleep(1); // Keep it responsive
    }
    return 0;
}


DWORD WINAPI AimbotThread(LPVOID lpParam) {
    Methods* methods = static_cast<Methods*>(lpParam);
    while (g_aimbotActive) {
        methods->aimbot();
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI EspThread(LPVOID lpParam) {
    HWND hwnd = FindWindowA(NULL, "AssaultCube");
    if (!hwnd) {
        std::cout << "[!] ESP: Failed to find AssaultCube window.\n";
        return 0;
    }

    while (g_espActive) {
        g_methods.esp(hwnd);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI GodThread(LPVOID lpParam) {
    while (g_godMode) {
        g_methods.godMode();
        Sleep(5); 
    }
    return 0;
}

void hook() {
    InitFunctionPointers();
    std::cout << "[+] Hook Initialized\n";
}


void console() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);


    std::cout << "[+] Console Initialized\n";
    std::cout << "Type 'help' to see available commands.\n";

    while (true) {
        std::string input;
        std::cin >> input;

        if (input == "exit") break;
        else if (input == "help") {
            std::cout << "Commands:\n";
            std::cout << "  help    - Show commands\n";
            std::cout << "  god     - Toggle God Mode\n";
            std::cout << "  aim     - Toggle Aimbot\n";
            std::cout << "  enemy   - Print enemy info\n";
            std::cout << "  name    - Print your player name\n";
			std::cout << "  recoil  - Toggle No Recoil\n";
			std::cout << "  esp     - Toggle ESP\n";
            std::cout << "  trigger - Toggle TriggerBot\n";
            std::cout << "  exit    - EXIT\n";

        }
        else if (input == "god") {
            if (!g_godMode) {
                g_godMode = true;
                hGodThread = CreateThread(nullptr, 0, GodThread, nullptr, 0, nullptr);
                std::cout << "[+] God Mode ON\n";
            }
            else {
                g_godMode = false;
                std::cout << "[-] God Mode OFF\n";
                if (hGodThread) {
                    WaitForSingleObject(hGodThread, INFINITE);
                    CloseHandle(hGodThread);
                    hGodThread = nullptr;
                }
            }
        }
        else if (input == "aim") {
            if (!g_aimbotActive) {
                g_aimbotActive = true;
                hAimbotThread = CreateThread(nullptr, 0, AimbotThread, &g_methods, 0, nullptr);
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
        else if (input == "esp") {
             if (!g_espActive) {
                g_espActive = true;
                hEspThread = CreateThread(nullptr, 0, EspThread, nullptr, 0, nullptr);
                std::cout << "[+] ESP ON\n";
             }
             else {
                g_espActive = false;
                if (hEspThread) {
                    WaitForSingleObject(hEspThread, INFINITE);
                    CloseHandle(hEspThread);
                    hEspThread = nullptr;
                }
                std::cout << "[-] ESP OFF\n";
             }
        }
        else if (input == "enemy") {
            g_methods.enemy();
        }
        else if (input == "name") {
            g_methods.printPlayerName();
        }
        else if (input == "recoil") {
            static bool recoilOff = false;
            recoilOff = !recoilOff;
            g_methods.recoil(recoilOff);
            std::cout << (recoilOff ? "[+] No Recoil ON\n" : "[-] No Recoil OFF\n");
        }
        else if (input == "trigger") {
            if (!g_triggerBot) {
                g_triggerBot = true;
                hTriggerThread = CreateThread(nullptr, 0, TriggerThread, nullptr, 0, nullptr);
                std::cout << "[+] TriggerBot ON\n";
            }
            else {
                g_triggerBot = false;
                if (hTriggerThread) {
                    WaitForSingleObject(hTriggerThread, INFINITE);
                    CloseHandle(hTriggerThread);
                    hTriggerThread = nullptr;
                }
                std::cout << "[-] TriggerBot OFF\n";
            }
        }

        else {
            std::cout << "[!] Unknown command. Type 'help'.\n";
        }
    }

    FreeConsole();
    ExitThread(0);
}

// Thread handles
HANDLE hConsoleThread = nullptr;
HANDLE hHookThread = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        hConsoleThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        hHookThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        FreeConsole();
        if (hConsoleThread) CloseHandle(hConsoleThread);
        //if (hHookThread) CloseHandle(hHookThread);
        break;
    }
    return TRUE;
}
