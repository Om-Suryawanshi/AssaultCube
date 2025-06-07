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
	bool patchAmmo(bool flag);
	bool godMode(bool flag);
	void printPlayerName();
    void aimbot();
    void enemy();

private:
    uintptr_t lastTarget = 0;
};