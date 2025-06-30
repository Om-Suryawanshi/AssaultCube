#pragma once
#include <Windows.h>

// Global Offsets
extern uintptr_t exeBaseAddr;
extern uintptr_t playerBaseOffset;
extern uintptr_t entListBaseOffset;
extern uintptr_t playerCount;
extern uintptr_t entLoopDistance;
extern uintptr_t gameState;
extern uintptr_t eyePos;
extern uintptr_t rotationOffset;

// Player offsets
extern uintptr_t playerHealthOffset;
extern uintptr_t playerNameOffset;
extern uintptr_t playerTeamOffset;
extern uintptr_t playerAmmoOffset;
extern uintptr_t playerArmorOffset;


extern uintptr_t viewMatrixOffset;

extern uintptr_t localPlayerAddr;
extern uintptr_t healthPatchAddr; // Intsn Addr
extern uintptr_t heathreturnAddr;
