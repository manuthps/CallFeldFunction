#pragma once
#include "ReversedFunctions.h"
#include "Network.h"
#include "Hook.h"

static int Sync = 0;
static int SyncPlayerAfterSettingMines = 0;
static int StartNewGameVar = 0;

class MineInit
{
public:
	ReversedFunctions	User;
	Network				Player;
	Hooker				HookFunc;

	MineInit(void);
	~MineInit(void);

	HANDLE ConsoleHandle;

	void GetUserInput();
	void SyncPlayer();
};

