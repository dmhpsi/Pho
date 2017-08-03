#pragma once
#define PI 3.14159265359f

typedef unsigned int MyEnum;

// Object type
#define NORMAL_OBJ 0
#define SKY_OBJ 1
#define BG_OBJ 2
#define MAN_OBJ 3
#define PHO_OBJ 4

// Object part
#define OBJ_MODEL 10
#define OBJ_TEXTURE 11
#define OBJ_SKY_TEXTURE 12
#define OBJ_SHADER 13
#define SCENE 14
#define OBJ_TEXT 15

// Function enum
#define FUNC_KEYUP 22
#define FUNC_KEYDOWN 23
#define FUNC_MOUSEUP 24
#define FUNC_MOUSEDOWN 25
#define FUNC_MOUSEMOVE 26

// Camera enum
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 4
#define MOVE_RIGHT 8
#define LOOK_UP 16
#define LOOK_DOWN 32
#define LOOK_LEFT 64
#define LOOK_RIGHT 128

#define DUCKING 256
#define FALLING 512
#define JUMPING 1024
#define RUSH 2048
#define FREE_MODE 4096
#define RESET 8192

#define MAX_COS 0.8

#define MID_CAM 1.8
#define LOW_CAM 0.6
#define HIGH_CAM 3.0


#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
	(byte & 0x8000 ? '1' : '0'), \
	(byte & 0x4000 ? '1' : '0'), \
	(byte & 0x2000 ? '1' : '0'), \
	(byte & 0x1000 ? '1' : '0'), \
	(byte & 0x800 ? '1' : '0'), \
	(byte & 0x400 ? '1' : '0'), \
	(byte & 0x200 ? '1' : '0'), \
	(byte & 0x100 ? '1' : '0'), \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0')