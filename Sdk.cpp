#include "pch.h"
#include "Sdk.h"
std::size_t getAddr(const char* moduleName, std::size_t Offset)
{
	std::size_t buffer = ((std::size_t)GetModuleHandleA(moduleName) + Offset);
	return buffer;
}

struct Vector3
{
	::std::float_t x;
	::std::float_t y;
	::std::float_t z;
};

class CPlayer  // Reversed player class out of memory using ReClass.NET, IDA Pro, x64dbg, and Cheat Engine
{
public:
	char pad_0000[144]; //0x0000
	int32_t m_iHealth; //0x0090
	char pad_0094[4012]; //0x0094

}; CPlayer* const Player = reinterpret_cast<CPlayer*>(getAddr("client.dll", LOCAL_PLAYER_OFFSET));