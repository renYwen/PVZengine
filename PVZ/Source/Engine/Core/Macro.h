#pragma once


constexpr float DELTA_TIME = 0.01f;
constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 600;

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;

#define DEFINE_SUPER(SuperClass) typedef SuperClass Super;