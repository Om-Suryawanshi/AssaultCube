#include "constants.h"

uintptr_t exeBaseAddr = (uintptr_t)GetModuleHandle(nullptr);
uintptr_t playerBaseOffset = 0x10F4F4;
uintptr_t entListBaseOffset = 0x10F4F8;
uintptr_t playerCount = 0x10F500;
uintptr_t entLoopDistance = 0x4; // how many bytes appart are different entities in the list
uintptr_t gameState = 0x10F49C;
uintptr_t eyePos = 0x4;
uintptr_t rotationOffset = 0x40;

// Player offsets
uintptr_t playerHealthOffset = 0xF8;
uintptr_t playerNameOffset = 0x225;
uintptr_t playerTeamOffset = 0x32C;
uintptr_t playerAmmoOffset = 0x150;
uintptr_t playerArmorOffset = 0xFC;

uintptr_t playerShootingOffset = 0x224; // 1 = Shooting, 0 = Not Shooting

uintptr_t viewMatrixOffset = 0x101AE8; 

uintptr_t localPlayerAddr = 0;
uintptr_t healthPatchAddr = exeBaseAddr + 0x29D1F;
uintptr_t heathreturnAddr = healthPatchAddr + 5;

uintptr_t weaponBaseOffset = 0x374; // Base pointer offset for weapon data

uintptr_t weaponRecoilOffset = 0x63786;

uintptr_t crosshairEntFunOffset = 0x607c0;
uintptr_t(__cdecl* GetCrossHairEnt)() = nullptr;

void InitFunctionPointers() {
    GetCrossHairEnt = (uintptr_t(__cdecl*)())(exeBaseAddr + crosshairEntFunOffset);
}