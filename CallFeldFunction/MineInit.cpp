#include "MineInit.h"


MineInit::MineInit(void)
{
}


MineInit::~MineInit(void)
{
}


void SetSyncState()
{
	Sync = 1;
}


void SetSyncStateAfterFlag()
{
	SyncPlayerAfterSettingMines = 1;
}


void SetSyncAfterSettingMinesFunc()
{
	if(Sync == 1)
	{
		SyncPlayerAfterSettingMines = 1;
	}
}


void ClickSmiley()
{
	StartNewGameVar = 1;
}


void MineInit::GetUserInput()
{
	BYTE JMP[] = {0xEB, 0x50};
	BYTE NOP[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	HookFunc.DetourFunc( ( BYTE* )0x1003512, ( BYTE* )&SetSyncState, 13 ); //10037E1 //Linker Mousebutton
	HookFunc.DetourFunc( ( BYTE* )0x100374F, ( BYTE* )&SetSyncStateAfterFlag, 13 ); //Rechter Mousebutton

	User.DisableMenu();

	User.SetFieldLength((BYTE)30);
	User.SetFieldHigh((BYTE)20);

	HookFunc.DetourFunc( ( BYTE* )0x1002913, ( BYTE* )&SetSyncAfterSettingMinesFunc, 13 );

	//Smiley Hook Click-Event (Sended NewGameRequest)
	HookFunc.DetourFunc( ( BYTE* )0x100145F, ( BYTE* )&ClickSmiley, 13 );
	BYTE JMPtoRTN[] = {0xEB, 0x76};
	User.PatchMem((PVOID)0x100146C, JMPtoRTN, sizeof(JMPtoRTN));

	User.PatchMem((PVOID)0x1003536, JMP, sizeof(JMP));					   //Setzt einen Jump zum ueberspringen, dass wenn der erste Klick auf eine Bombe
																		   //erfolgt, dieses Feld als NICHT-Bombe angesehen wird


	Player.Connect();
	FreeConsole();
	while(1)
	{
		/*if(GetAsyncKeyState(VK_F4) & 1)
		{
			User.SetFieldColered(0);
			printf("\nFeld schwarz/weiss gemacht.");
		}
		else if(GetAsyncKeyState(VK_F5) & 1)
		{
			User.SetFieldColered(1);
			printf("\nFeld farbig gemacht.");
		}*/
		/*else if(GetAsyncKeyState(VK_F4) & 1)
		{
			User.SetSmiley(0);
			printf("\nLaechelnder Smiley");
		}
		else if(GetAsyncKeyState(VK_F5) & 1)
		{
			User.SetSmiley(1);
			printf("\nSmiley mit Mund auf");
		}
		else if(GetAsyncKeyState(VK_F6) & 1)
		{
			User.SetSmiley(2);
			printf("\nToder Smiley");
		}
		else if(GetAsyncKeyState(VK_F7) & 1)
		{
			User.SetSmiley(3);
			printf("\nSmiley mit Sonnenbrille");
		}*/

		//Checkt alle eingehenden Pakete vom Server ab
		Player.CheckIncomingPackets();
		SyncPlayer();
		Sleep(10);
	}
}


void MineInit::SyncPlayer()
{
	if(SyncPlayerAfterSettingMines == 1)
	{
		User.FreezeField();
		Player.SendField();
		Player.SendBombCount();
		Player.SendTime();
		//User.CheckGameState();
		if(User.GetSmiley() == 2)
		{
			Player.SendGameState(2);//Verloren
			User.SetFieldColered(1);
		}
		else if(User.GetSmiley() == 3)
		{
			Player.SendGameState(3);//Gewonnen
			User.SetFieldColered(1);
		}
		else
		{
			User.SetFieldColered(0);
		}
		Player.SendAmountOpenedMines();

		Sync = 0;
		SyncPlayerAfterSettingMines = 0;
	}

	if(StartNewGameVar == 1)
	{
		StartNewGameVar = 0;
		Player.SendNewGameRequest();
		StartNewGameVar = 0;
	}
}