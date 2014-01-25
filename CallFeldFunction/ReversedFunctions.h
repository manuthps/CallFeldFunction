#pragma once
#include "Network.h"
//#include <Windows.h>

class ReversedFunctions
{
public:
	ReversedFunctions(void);
	~ReversedFunctions(void);

	void __stdcall SetMine(BYTE, BYTE, BYTE);
	BYTE GetMine(int X, int Y);
	void RestartGame();
	const char* GetTime();
	void SetTime(const char* Count);
	const char* GetBombs();
	void PatchMem(LPVOID dwAddress, LPVOID bytes, DWORD dwSize);
	BYTE ReadMem(LPVOID dwAddress, BYTE bytes);
	void SetBombCount(const char* Count);
	const char* GetAllMines();
	int GetSmiley();
	const char*  GetAmountOpenedMines();
	void SetAmountOpenedMines(const char* Value);
	void SetAllMines(const char* Mines);
	void RefreshScreen();
	void StartGameFirstTime();
	void FreezeField();
	void UnFreezeField();
	void SetSmiley(const char* Value);
	void ClearField();
	void RestartGame2(int High, int Length);
	void CheckGameState();
	void SetGameState(int State);
	int GetFieldLength();
	void SetFieldLength(BYTE Length);
	int GetFieldHigh();
	void SetFieldHigh(BYTE High);
	void SetMineCounter(BYTE Counter);
	void SetFieldColered(BYTE State);
	void DisableMenu();
};

