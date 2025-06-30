#pragma once
#include <Windows.h>
#include <math.h>

class Methods {
public:
    struct Vec3 {
        float x, y, z;

        float distanceTo(const Vec3& other) const {
            return sqrtf((x - other.x) * (x - other.x) +
                (y - other.y) * (y - other.y) +
                (z - other.z) * (z - other.z));
        }
    };

    struct Vec2 {
        float x, y;
    };

    //bool patchAmmo(bool flag);
    void godMode();
    void printPlayerName();
    void aimbot();
    void enemy();

    //ESP
    bool WorldToScreen(const Methods::Vec3& pos, Methods::Vec2& screen, float matrix[16], int width, int height);
    void esp(HWND gameHwnd);



private:
    uintptr_t lastTarget = 0;
};

//extern "C" void __declspec(naked) HealthHook();