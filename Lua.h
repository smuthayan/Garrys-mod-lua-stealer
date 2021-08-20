#pragma once
#include "pch.h"

#ifndef LUA_H
#define LUA_H

namespace Lua
{
	static ::std::uint64_t count = 1;
	static ::std::uint64_t howManySameStrings = 0;
	static std::vector<std::string> filenameArray(1, 0);
	std::string IntToString(::std::uint64_t x);
	void checkIfNameIsRepeat(std::string& string);
	void removeIllegalChars(std::string& string);

};
#endif