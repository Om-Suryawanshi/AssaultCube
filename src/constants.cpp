#include "constants.h"

uintptr_t exeBaseAddr = (uintptr_t)GetModuleHandle(nullptr);
uintptr_t playerBaseOffset = 0x10F4F4;
uintptr_t entListBaseOffset = 0x10F4F8;
uintptr_t playerCount = 0x10F500;
uintptr_t entLoopDistance = 0x4; // how many bytes appart are different entities in the list
uintptr_t gameState = 0x10F49C;
uintptr_t eyePos = 0x4;
uintptr_t rotationOffset = 0x40;
uintptr_t playerHealthOffset = 0xF8;
uintptr_t playerNameOffset = 0x225;
uintptr_t playerTeamOffset = 0x32C;