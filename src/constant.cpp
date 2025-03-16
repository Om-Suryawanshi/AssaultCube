#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddr = (uintptr_t)GetModuleHandle(nullptr);

extern Player* localPlayerPtr = *(Player**)(exeBaseAddr + 0x0010F4F4);