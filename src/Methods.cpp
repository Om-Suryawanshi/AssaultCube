#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "genCode.h"
#include "constants.h"
#include "Methods.h"


bool Methods::patchAmmo(bool flag) {
    DWORD oldProtect;
    DWORD ammoPatchAddr = exeBaseAddr + 0x637E9;
    BYTE* ammoAddr = (BYTE*)ammoPatchAddr;

    if (!flag) {
        VirtualProtect(ammoAddr, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
        ammoAddr[0] = 0x90; //NOP
        ammoAddr[1] = 0x90; //NOP
        VirtualProtect(ammoAddr, 2, oldProtect, &oldProtect);
        std::cout << "[+] Infinite Ammo Activated!" << std::endl;
        flag = !flag;
    }
    else {
        VirtualProtect(ammoAddr, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
        ammoAddr[0] = 0xFF;
        ammoAddr[1] = 0x0E;
        VirtualProtect(ammoAddr, 2, oldProtect, &oldProtect);
        flag = !flag;
        std::cout << "[-] Infinite Ammo Deactivated!" << std::endl;
    }
    return flag;
}

bool Methods::godMode(bool flag) {
    DWORD oldProtect;
    DWORD healthPatchAddr = exeBaseAddr + 0x29D1F;
    BYTE* healthAddr = (BYTE*)healthPatchAddr;

    if (!flag) {
        VirtualProtect(healthAddr, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
        healthAddr[0] = 0x90;  // NOP (No Operation) - Prevents health reduction
        healthAddr[1] = 0x90;
        healthAddr[2] = 0x90;
        VirtualProtect(healthAddr, 3, oldProtect, &oldProtect);
        std::cout << "[+] God Mode Activated!" << std::endl;
        flag = !flag;
    }
    else {
        VirtualProtect(healthAddr, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
        healthAddr[0] = 0x29; 
        healthAddr[1] = 0x7B;
        healthAddr[2] = 0x04;
        VirtualProtect(healthAddr, 3, oldProtect, &oldProtect);
        std::cout << "[-] God Mode Deactivated!" << std::endl;
        flag = !flag;
    }
    return flag;
}