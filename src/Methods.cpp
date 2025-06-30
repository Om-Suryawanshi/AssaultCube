#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "constants.h"
#include "Methods.h"
#include <cmath>
#include <string>

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



void Methods::printPlayerName() {
    uintptr_t playerBase = *(uintptr_t*)(exeBaseAddr + playerBaseOffset);
    if (playerBase == 0) {
        std::cout << "[-] Player base not found!" << std::endl;
        return;
    }
    char playerName[32] = { 0 };
    memcpy(playerName, (void*)(playerBase + playerNameOffset), sizeof(playerName) - 1);
    std::cout << "[+] Player Name: " << playerName << std::endl;
}

void Methods::enemy() {
	std::cout << "[+] Enemy list.\n";
    uintptr_t entityList = *(uintptr_t*)(exeBaseAddr + entListBaseOffset);
	uintptr_t player = *(uintptr_t*)(exeBaseAddr + playerBaseOffset);
	int playerTeam = *(int*)(player + playerTeamOffset);
    if (!entityList) {
        std::cout << "[-] Entity list not found!" << std::endl;
        return;
    }
    int count = *(int*)(exeBaseAddr + playerCount);
    for (int i = 0; i < count; ++i) {
        uintptr_t entity = *(uintptr_t*)(entityList + i * entLoopDistance);
        if (!entity) continue;
        int health = *(int*)(entity + playerHealthOffset);
        if (health <= 0) continue;
        char name[32] = { 0 };
        memcpy(name, (void*)(entity + playerNameOffset), sizeof(name) - 1);
        int team = *(int*)(entity + playerTeamOffset);
        if (team == playerTeam) {
			std::cout << "[*] Teammate " << i << ": " << name << "| Health: " << health << " | Team: " << team << std::endl;
        }
        else {
            std::cout << "[+] Enemy " << i << ": " << name << " | Health: " << health << " | Team: " << team << std::endl;
        }
	}
}

void Methods::aimbot() {
    uintptr_t localPlayer = *(uintptr_t*)(exeBaseAddr + playerBaseOffset);
    if (!localPlayer) return;

    Vec3 localPos = *(Vec3*)(localPlayer + 0x4);
    int localTeam = *(int*)(localPlayer + playerTeamOffset);
    float currentYaw = *(float*)(localPlayer + rotationOffset);

    uintptr_t entityList = *(uintptr_t*)(exeBaseAddr + entListBaseOffset);
    int count = *(int*)(exeBaseAddr + playerCount);

    // Step 1: Check if previous target is still valid
    bool validLast = false;
    if (lastTarget) {
        int health = *(int*)(lastTarget + playerHealthOffset);
        int team = *(int*)(lastTarget + playerTeamOffset);
        validLast = (health > 0 && team != localTeam);
    }

    uintptr_t target = lastTarget;

    // Step 2: If not valid, find new closest target
    if (!validLast) {
        float smallestAngle = FLT_MAX;
        target = 0;

        for (int i = 0; i < count; ++i) {
            uintptr_t entity = *(uintptr_t*)(entityList + i * 4);
            if (!entity || entity == localPlayer) continue;

            int health = *(int*)(entity + playerHealthOffset);
            int team = *(int*)(entity + playerTeamOffset);
            if (health <= 0 || team == localTeam) continue;

            Vec3 enemyPos = *(Vec3*)(entity + 0x4);

            float dx = enemyPos.x - localPos.x;
            float dy = enemyPos.y - localPos.y;

            float yaw = atan2f(dx, -dy) * (180.0f / 3.14159265f);
            if (yaw < 0) yaw += 360.0f;

            float deltaYaw = fabsf(currentYaw - yaw);
            if (deltaYaw > 180.0f) deltaYaw = 360.0f - deltaYaw;

            if (deltaYaw < smallestAngle) {
                smallestAngle = deltaYaw;
                target = entity;
            }
        }

        lastTarget = target; // Update last target if found
    }

    // Step 3: Aim at target if valid
    if (target) {
        Vec3 enemyPos = *(Vec3*)(target + 0x4);

        float dx = enemyPos.x - localPos.x;
        float dy = enemyPos.y - localPos.y;
        float dz = enemyPos.z - localPos.z;

        float yaw = atan2f(dx, -dy) * (180.0f / 3.14159265f);
        if (yaw < 0) yaw += 360.0f;

        float distanceFlat = sqrtf(dx * dx + dy * dy);
        float pitch = atanf(dz / distanceFlat) * (180.0f / 3.14159265f);

        *(float*)(localPlayer + rotationOffset) = yaw;
        *(float*)(localPlayer + rotationOffset + 0x4) = pitch;

        //std::cout << "[+] Tracking enemy (Yaw: " << yaw << ", Pitch: " << pitch << ")\n";
    }
}

bool Methods::WorldToScreen(const Methods::Vec3& pos, Methods::Vec2& screen, float matrix[16], int width, int height) {
    float clipX = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    float clipY = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    float clipW = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipW < 0.1f) return false;

    float ndcX = clipX / clipW;
    float ndcY = clipY / clipW;

    screen.x = (width / 2.0f * ndcX) + (width / 2.0f);
    screen.y = -(height / 2.0f * ndcY) + (height / 2.0f);

    return true;
}

void Methods::esp(HWND hwnd) {
    RECT gameRect;
    if (!GetClientRect(hwnd, &gameRect)) return;

    int width = gameRect.right;
    int height = gameRect.bottom;

    //std::cout << "Height : " << height << " Width : " << width;

    HDC hdc = GetDC(hwnd);
    if (!hdc) return;

    uintptr_t localPlayer = *(uintptr_t*)(exeBaseAddr + playerBaseOffset);
    if (!localPlayer) return;

    Vec3 localPos = *(Vec3*)(localPlayer + 0x4);
    int localTeam = *(int*)(localPlayer + playerTeamOffset);

    uintptr_t entityList = *(uintptr_t*)(exeBaseAddr + entListBaseOffset);
    int count = *(int*)(exeBaseAddr + playerCount);

    float* viewMatrix = (float*)(exeBaseAddr + viewMatrixOffset);  // Ensure this offset is correct

    for (int i = 0; i < count; ++i) {
        uintptr_t entity = *(uintptr_t*)(entityList + i * 4);
        if (!entity || entity == localPlayer) continue;

        int health = *(int*)(entity + playerHealthOffset);
        int team = *(int*)(entity + playerTeamOffset);
        if (health <= 0 || team == localTeam) continue;

        Vec3 enemyPos = *(Vec3*)(entity + 0x4);
        Vec2 screenPos;
        if (WorldToScreen(enemyPos, screenPos, viewMatrix, width, height)) {
            // Draw rectangle at screenPos
            int boxWidth = 40;
            int boxHeight = 80;

            int x = static_cast<int>(screenPos.x - boxWidth / 2);
            int y = static_cast<int>(screenPos.y - boxHeight / 2);

            HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Red color for enemies
            HGDIOBJ oldPen = SelectObject(hdc, pen);
            HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH)); // No fill

            Rectangle(hdc, x, y, x + boxWidth, y + boxHeight);

            SelectObject(hdc, oldBrush);
            SelectObject(hdc, oldPen);
            DeleteObject(pen);
        }
    }

    ReleaseDC(hwnd, hdc);
}
