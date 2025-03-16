#pragma once

class Vector3 {
public:
	float x;
	float z;
	float y;
};

class Player
{
public:
	char pad_0000[4]; //0x0000
	Vector3 PlayerHeadPos; //0x0004
	Vector3 Velocity; //0x0010
	char pad_001C[24]; //0x001C
	Vector3 PlayerFeetPos; //0x0034
	float yaw; //0x0040
	float pitch; //0x0044
	float roll; //0x0048
	char pad_004C[396]; //0x004C
}; //Size: 0x01D8