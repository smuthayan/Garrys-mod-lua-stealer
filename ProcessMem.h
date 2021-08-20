#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <strsafe.h>


void ErrorExit(const char* lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		(LPCVOID)LANG_USER_DEFAULT,
		dw,
		LANG_USER_DEFAULT,
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}


class ProcessMem
{
public:


	template <typename T>
	T ReadMemory(HANDLE hProc, ::std::uint32_t Address)
	{
		T Buffer = 0;
		if (!ReadProcessMemory(hProc, (BYTE*)Address, &Buffer, sizeof(Address), NULL))
		{
			ErrorExit("ReadProcessMemory");
		}

		return Buffer;

	}

	template <typename T>
	T WriteMemory(HANDLE hProc, ::std::uint32_t Address, LPVOID data)
	{
		
		if (!WriteProcessMemory(hProc, (BYTE*)Address, data, sizeof(Address), NULL))
		{
			ErrorExit("WriteProcessMemory");
		} 

		return 0;
	}




	::std::uint32_t GetPID(const char* windowName)
	{
		::std::uint32_t pID = 0;
		HWND hWindow = FindWindowA(NULL, windowName);
		if (!FindWindowA)
		{
			ErrorExit("FindWindowA");
		}

		if (!GetWindowThreadProcessId(hWindow, (LPDWORD)&pID))
		{
			ErrorExit("GetWindowThreadProcessId");
		}
		return pID;
	}

	::std::uint32_t getBaseAddress(HANDLE hProc, const wchar_t* moduleName, const ::std::uint32_t baseOffset)
	{
		MODULEENTRY32 me32;
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessId(hProc));
		if (!CreateToolhelp32Snapshot)
		{
			ErrorExit("CreateToolhelp32Snapshot");
		}
		me32.dwSize = sizeof(MODULEENTRY32);
		Module32First(hSnap, &me32);
		do
		{
			if (wcscmp(moduleName, me32.szModule) == 0)
			{
				break;
			}

		} while (Module32Next(hSnap, &me32));
		return ReadMemory<::std::uint32_t>(hProc, (::std::uint32_t)me32.modBaseAddr + baseOffset);

	}




	::std::uint32_t resolveAddress(std::vector<::std::uint32_t> Offsets, ::std::uint32_t baseAddress)
	{

		for (::std::uint32_t x = 0; x < Offsets.size(); ++x)
		{

			baseAddress += Offsets[x];
		}

		return baseAddress;
	}

	ProcessMem()
	{

	}
	
	~ProcessMem()
	{
	
	}

};

