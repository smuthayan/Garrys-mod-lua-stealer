#pragma once
#include "pch.h"
#include "Lua.h"
#ifndef HOOKING_H
#define HOOKING_H

// Function prototype in the target dll
int(__fastcall* luaL_LoadBufferx)(void*, const char*, size_t, const char*, const char* mode) = reinterpret_cast<int(__fastcall*)(void*, const char*, size_t, const char*, const char* mode)>(GetProcAddress(GetModuleHandleA("lua_shared.dll"),"luaL_loadbufferx"));


int __fastcall luaL_LoadBufferHOOKED(void* lua_State, const char* buff, size_t sz, const char* name, const char* mode)
{

		std::string fileName = name;
		Lua::checkIfNameIsRepeat(fileName);
		Lua::removeIllegalChars(fileName); // finished here
		fileName = "C:\\STOLEN_LUA\\" + fileName;
		std::size_t found = fileName.find(".lua");
		if (found != std::string::npos)
		{
			
		}
		else
		{
			fileName += ".lua"; 
		}


		std::ofstream file;
		file.open(fileName);
		std::cout << "[+]" << "File created: " << fileName;
		file << buff;

	return luaL_LoadBufferx(lua_State, buff, sz, name, mode);
}
#endif