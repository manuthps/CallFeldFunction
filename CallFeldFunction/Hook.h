#pragma once
#include <stdio.h>
#include <Windows.h>

class Hooker
{
public:
	Hooker(void);
	~Hooker(void);

	bool DetourFunc(BYTE* oldFunc, BYTE* newFunc, DWORD len);
};

