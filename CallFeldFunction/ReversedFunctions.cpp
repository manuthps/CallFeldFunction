#include "ReversedFunctions.h"

DWORD Spielfeld[24][30] = 
{
	{0x01005361, 0x01005362, 0x01005363, 0x01005364, 0x01005365, 0x01005366, 0x01005367, 0x01005368, 0x01005369, 0x0100536A, 0x0100536B, 0x0100536C, 0x0100536D, 0x0100536E, 0x0100536F, 0x01005370, 0x01005371, 0x01005372, 0x01005373, 0x01005374, 0x01005375, 0x01005376, 0x01005377, 0x01005378, 0x01005379, 0x0100537A, 0x0100537B, 0x0100537C, 0x0100537D, 0x0100537E},
	{0x01005381, 0x01005382, 0x01005383, 0x01005384, 0x01005385, 0x01005386, 0x01005387, 0x01005388, 0x01005389, 0x0100538A, 0x0100538B, 0x0100538C, 0x0100538D, 0x0100538E, 0x0100538F, 0x01005390, 0x01005391, 0x01005392, 0x01005393, 0x01005394, 0x01005395, 0x01005396, 0x01005397, 0x01005398, 0x01005399, 0x0100539A, 0x0100539B, 0x0100539C, 0x0100539D, 0x0100539E},
	{0x010053A1, 0x010053A2, 0x010053A3, 0x010053A4, 0x010053A5, 0x010053A6, 0x010053A7, 0x010053A8, 0x010053A9, 0x010053AA, 0x010053AB, 0x010053AC, 0x010053AD, 0x010053AE, 0x010053AF, 0x010053B0, 0x010053B1, 0x010053B2, 0x010053B3, 0x010053B4, 0x010053B5, 0x010053B6, 0x010053B7, 0x010053B8, 0x010053B9, 0x010053BA, 0x010053BB, 0x010053BC, 0x010053BD, 0x010053BE},
	{0x010053C1, 0x010053C2, 0x010053C3, 0x010053C4, 0x010053C5, 0x010053C6, 0x010053C7, 0x010053C8, 0x010053C9, 0x010053CA, 0x010053CB, 0x010053CC, 0x010053CD, 0x010053CE, 0x010053CF, 0x010053D0, 0x010053D1, 0x010053D2, 0x010053D3, 0x010053D4, 0x010053D5, 0x010053D6, 0x010053D7, 0x010053D8, 0x010053D9, 0x010053DA, 0x010053DB, 0x010053DC, 0x010053DD, 0x010053DE},
	{0x010053E1, 0x010053E2, 0x010053E3, 0x010053E4, 0x010053E5, 0x010053E6, 0x010053E7, 0x010053E8, 0x010053E9, 0x010053EA, 0x010053EB, 0x010053EC, 0x010053ED, 0x010053EE, 0x010053EF, 0x010053F0, 0x010053F1, 0x010053F2, 0x010053F3, 0x010053F4, 0x010053F5, 0x010053F6, 0x010053F7, 0x010053F8, 0x010053F9, 0x010053FA, 0x010053FB, 0x010053FC, 0x010053FD, 0x010053FE},
	{0x01005401, 0x01005402, 0x01005403, 0x01005404, 0x01005405, 0x01005406, 0x01005407, 0x01005408, 0x01005409, 0x0100540A, 0x0100540B, 0x0100540C, 0x0100540D, 0x0100540E, 0x0100540F, 0x01005410, 0x01005411, 0x01005412, 0x01005413, 0x01005414, 0x01005415, 0x01005416, 0x01005417, 0x01005418, 0x01005419, 0x0100541A, 0x0100541B, 0x0100541C, 0x0100541D, 0x0100541E},
	{0x01005421, 0x01005422, 0x01005423, 0x01005424, 0x01005425, 0x01005426, 0x01005427, 0x01005428, 0x01005429, 0x0100542A, 0x0100542B, 0x0100542C, 0x0100542D, 0x0100542E, 0x0100542F, 0x01005430, 0x01005431, 0x01005432, 0x01005433, 0x01005434, 0x01005435, 0x01005436, 0x01005437, 0x01005438, 0x01005439, 0x0100543A, 0x0100543B, 0x0100543C, 0x0100543D, 0x0100543E},
	{0x01005441, 0x01005442, 0x01005443, 0x01005444, 0x01005445, 0x01005446, 0x01005447, 0x01005448, 0x01005449, 0x0100544A, 0x0100544B, 0x0100544C, 0x0100544D, 0x0100544E, 0x0100544F, 0x01005450, 0x01005451, 0x01005452, 0x01005453, 0x01005454, 0x01005455, 0x01005456, 0x01005457, 0x01005458, 0x01005459, 0x0100545A, 0x0100545B, 0x0100545C, 0x0100545D, 0x0100545E},
	{0x01005461, 0x01005462, 0x01005463, 0x01005464, 0x01005465, 0x01005466, 0x01005467, 0x01005468, 0x01005469, 0x0100546A, 0x0100546B, 0x0100546C, 0x0100546D, 0x0100546E, 0x0100546F, 0x01005470, 0x01005471, 0x01005472, 0x01005473, 0x01005474, 0x01005475, 0x01005476, 0x01005477, 0x01005478, 0x01005479, 0x0100547A, 0x0100547B, 0x0100547C, 0x0100547D, 0x0100547E},
	{0x01005481, 0x01005482, 0x01005483, 0x01005484, 0x01005485, 0x01005486, 0x01005487, 0x01005488, 0x01005489, 0x0100548A, 0x0100548B, 0x0100548C, 0x0100548D, 0x0100548E, 0x0100548F, 0x01005490, 0x01005491, 0x01005492, 0x01005493, 0x01005494, 0x01005495, 0x01005496, 0x01005497, 0x01005498, 0x01005499, 0x0100549A, 0x0100549B, 0x0100549C, 0x0100549D, 0x0100549E},
	{0x010054A1, 0x010054A2, 0x010054A3, 0x010054A4, 0x010054A5, 0x010054A6, 0x010054A7, 0x010054A8, 0x010054A9, 0x010054AA, 0x010054AB, 0x010054AC, 0x010054AD, 0x010054AE, 0x010054AF, 0x010054B0, 0x010054B1, 0x010054B2, 0x010054B3, 0x010054B4, 0x010054B5, 0x010054B6, 0x010054B7, 0x010054B8, 0x010054B9, 0x010054BA, 0x010054BB, 0x010054BC, 0x010054BD, 0x010054BE},
	{0x010054C1, 0x010054C2, 0x010054C3, 0x010054C4, 0x010054C5, 0x010054C6, 0x010054C7, 0x010054C8, 0x010054C9, 0x010054CA, 0x010054CB, 0x010054CC, 0x010054CD, 0x010054CE, 0x010054CF, 0x010054D0, 0x010054D1, 0x010054D2, 0x010054D3, 0x010054D4, 0x010054D5, 0x010054D6, 0x010054D7, 0x010054D8, 0x010054D9, 0x010054DA, 0x010054DB, 0x010054DC, 0x010054DD, 0x010054DE},
	{0x010054E1, 0x010054E2, 0x010054E3, 0x010054E4, 0x010054E5, 0x010054E6, 0x010054E7, 0x010054E8, 0x010054E9, 0x010054EA, 0x010054EB, 0x010054EC, 0x010054ED, 0x010054EE, 0x010054EF, 0x010054F0, 0x010054F1, 0x010054F2, 0x010054F3, 0x010054F4, 0x010054F5, 0x010054F6, 0x010054F7, 0x010054F8, 0x010054F9, 0x010054FA, 0x010054FB, 0x010054FC, 0x010054FD, 0x010054FE}, //
	{0x01005501, 0x01005502, 0x01005503, 0x01005504, 0x01005505, 0x01005506, 0x01005507, 0x01005508, 0x01005509, 0x0100550A, 0x0100550B, 0x0100550C, 0x0100550D, 0x0100550E, 0x0100550F, 0x01005510, 0x01005511, 0x01005512, 0x01005513, 0x01005514, 0x01005515, 0x01005516, 0x01005517, 0x01005518, 0x01005519, 0x0100551A, 0x0100551B, 0x0100551C, 0x0100551D, 0x0100551E},
	{0x01005521, 0x01005522, 0x01005523, 0x01005524, 0x01005525, 0x01005526, 0x01005527, 0x01005528, 0x01005529, 0x0100552A, 0x0100552B, 0x0100552C, 0x0100552D, 0x0100552E, 0x0100552F, 0x01005530, 0x01005531, 0x01005532, 0x01005533, 0x01005534, 0x01005535, 0x01005536, 0x01005537, 0x01005538, 0x01005539, 0x0100553A, 0x0100553B, 0x0100553C, 0x0100553D, 0x0100553E},
	{0x01005541, 0x01005542, 0x01005543, 0x01005544, 0x01005545, 0x01005546, 0x01005547, 0x01005548, 0x01005549, 0x0100554A, 0x0100554B, 0x0100554C, 0x0100554D, 0x0100554E, 0x0100554F, 0x01005550, 0x01005551, 0x01005552, 0x01005553, 0x01005554, 0x01005555, 0x01005556, 0x01005557, 0x01005558, 0x01005559, 0x0100555A, 0x0100555B, 0x0100555C, 0x0100555D, 0x0100555E},
	{0x01005561, 0x01005562, 0x01005563, 0x01005564, 0x01005565, 0x01005566, 0x01005567, 0x01005568, 0x01005569, 0x0100556A, 0x0100556B, 0x0100556C, 0x0100556D, 0x0100556E, 0x0100556F, 0x01005570, 0x01005571, 0x01005572, 0x01005573, 0x01005574, 0x01005575, 0x01005576, 0x01005577, 0x01005578, 0x01005579, 0x0100557A, 0x0100557B, 0x0100557C, 0x0100557D, 0x0100557E},
	{0x01005581, 0x01005582, 0x01005583, 0x01005584, 0x01005585, 0x01005586, 0x01005587, 0x01005588, 0x01005589, 0x0100558A, 0x0100558B, 0x0100558C, 0x0100558D, 0x0100558E, 0x0100558F, 0x01005590, 0x01005591, 0x01005592, 0x01005593, 0x01005594, 0x01005595, 0x01005596, 0x01005597, 0x01005598, 0x01005599, 0x0100559A, 0x0100559B, 0x0100559C, 0x0100559D, 0x0100559E},
	{0x010055A1, 0x010055A2, 0x010055A3, 0x010055A4, 0x010055A5, 0x010055A6, 0x010055A7, 0x010055A8, 0x010055A9, 0x010055AA, 0x010055AB, 0x010055AC, 0x010055AD, 0x010055AE, 0x010055AF, 0x010055B0, 0x010055B1, 0x010055B2, 0x010055B3, 0x010055B4, 0x010055B5, 0x010055B6, 0x010055B7, 0x010055B8, 0x010055B9, 0x010055BA, 0x010055BB, 0x010055BC, 0x010055BD, 0x010055BE},
	{0x010055C1, 0x010055C2, 0x010055C3, 0x010055C4, 0x010055C5, 0x010055C6, 0x010055C7, 0x010055C8, 0x010055C9, 0x010055CA, 0x010055CB, 0x010055CC, 0x010055CD, 0x010055CE, 0x010055CF, 0x010055D0, 0x010055D1, 0x010055D2, 0x010055D3, 0x010055D4, 0x010055D5, 0x010055D6, 0x010055D7, 0x010055D8, 0x010055D9, 0x010055DA, 0x010055DB, 0x010055DC, 0x010055DD, 0x010055DE},
	{0x010055E1, 0x010055E2, 0x010055E3, 0x010055E4, 0x010055E5, 0x010055E6, 0x010055E7, 0x010055E8, 0x010055E9, 0x010055EA, 0x010055EB, 0x010055EC, 0x010055ED, 0x010055EE, 0x010055EF, 0x010055F0, 0x010055F1, 0x010055F2, 0x010055F3, 0x010055F4, 0x010055F5, 0x010055F6, 0x010055F7, 0x010055F8, 0x010055F9, 0x010055FA, 0x010055FB, 0x010055FC, 0x010055FD, 0x010055FE}, //
	{0x01005601, 0x01005602, 0x01005603, 0x01005604, 0x01005605, 0x01005606, 0x01005607, 0x01005608, 0x01005609, 0x0100560A, 0x0100560B, 0x0100560C, 0x0100560D, 0x0100560E, 0x0100560F, 0x01005610, 0x01005611, 0x01005612, 0x01005613, 0x01005614, 0x01005615, 0x01005616, 0x01005617, 0x01005618, 0x01005619, 0x0100561A, 0x0100561B, 0x0100561C, 0x0100561D, 0x0100561E},
	{0x01005621, 0x01005622, 0x01005623, 0x01005624, 0x01005625, 0x01005626, 0x01005627, 0x01005628, 0x01005629, 0x0100562A, 0x0100562B, 0x0100562C, 0x0100562D, 0x0100562E, 0x0100562F, 0x01005630, 0x01005631, 0x01005632, 0x01005633, 0x01005634, 0x01005635, 0x01005636, 0x01005637, 0x01005638, 0x01005639, 0x0100563A, 0x0100563B, 0x0100563C, 0x0100563D, 0x0100563E},
	{0x01005641, 0x01005642, 0x01005643, 0x01005644, 0x01005645, 0x01005646, 0x01005647, 0x01005648, 0x01005649, 0x0100564A, 0x0100564B, 0x0100564C, 0x0100564D, 0x0100564E, 0x0100564F, 0x01005650, 0x01005651, 0x01005652, 0x01005653, 0x01005654, 0x01005655, 0x01005656, 0x01005657, 0x01005658, 0x01005659, 0x0100565A, 0x0100565B, 0x0100565C, 0x0100565D, 0x0100565E}
};


ReversedFunctions::ReversedFunctions(void)
{
}


ReversedFunctions::~ReversedFunctions(void)
{
}


//Callback zum Minen setzen X, Y, Art der Mine
void __stdcall ReversedFunctions::SetMine(BYTE X, BYTE Y, BYTE Art)
{
	typedef void (__stdcall *pFunctionAddress)(BYTE, BYTE, BYTE);
	pFunctionAddress pMySecretFunction = (pFunctionAddress)(0x1002EAB);
	pMySecretFunction(X, Y, Art);
}


BYTE ReversedFunctions::GetMine(int X, int Y)
{
	return *(BYTE*)Spielfeld[X][Y];
}


void ReversedFunctions::RestartGame()
{
	//Setzt einen JMP, der die Routine fuer das zufaellige Bomben-Legen uebergeht
	BYTE JUMP[] = {0xEB, 0x3C};
	PatchMem((PVOID)0x10036C7, JUMP, 2);


	//Ruft die Funktion zum GameRestart auf (Timer, Felder, etc. zuruecksetzen)
	//Die Bombem setzen wir spaeter manuell
	DWORD func = 0x100367A;
	__asm CALL func
}


void ReversedFunctions::RestartGame2(int High, int Laength)
{
	BYTE Patch[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; //Patched aus der "Neues Spiel starten" Funktion das Automatische Feld-Setzen raus
	PatchMem((PVOID)0x10038AF, Patch, 7);
	Sleep(100);

	BYTE JUMP[] = {0x00, 0x00, 0x00, 0x00}, JUMP2[] = {0x04, 0x00, 0x00, 0x00};
	BYTE JUMP3[] = {0x06, 0x00, 0x00, 0x00}, JUMP4[] = {0x09, 0x00, 0x00, 0x00};
	PatchMem((PVOID)0x10057A4, JUMP, 4);
	PatchMem((PVOID)0x100579C, JUMP, 4);
	PatchMem((PVOID)0x100511C, JUMP2, 4);
	PatchMem((PVOID)0x1005118, JUMP3, 4);


	//Ruft die Funktion zum GameRestart auf (Timer, Felder, etc. zuruecksetzen)
	//Die Bombem setzen wir spaeter manuell
	DWORD func = 0x10037E1;
	PatchMem((PVOID)0x10057A4, JUMP, 0);
	__asm CALL func
	Sleep(100);
	
	
	BYTE Patch1[] = {0x51};
	BYTE Patch2[] = {0x50};
	BYTE Patch3[] = {0xE8, 0x5C, 0xFC, 0xFF, 0xFF};
	PatchMem((PVOID)0x10038AF, Patch1, 1);
	PatchMem((PVOID)0x10038B0, Patch2, 1);
	PatchMem((PVOID)0x10038B1, Patch3, 5);
	

	/*HWND hWindow = FindWindow(NULL, TEXT("MineSweeper")); //winmine
	UINT nIDEvent = 0x3E8;
	UINT uElapse = 0x1;
	DWORD lpTimerFunc = 0x1005B24;
	SetTimer(hWindow, nIDEvent, uElapse, (TIMERPROC)lpTimerFunc);*/
}


//Gibt den Wert des Timers zurueck
const char* ReversedFunctions::GetTime()
{
	char PackedID[8] = " ";
	PackedID[0] = 'T';
	static char rtnString[4] = " ";
	sprintf(rtnString, "%d", *(int*)(0x100579C));
	strcat(PackedID, rtnString);
	return PackedID;
}


void ReversedFunctions::SetTime(const char* Count)
{
	WORD Time = atoi(Count);
	PatchMem((PVOID)0x100579C, &Time, sizeof(Time));
	RefreshScreen();
}


//Gibt dern Wert des Bomben-Counters zurueck
const char* ReversedFunctions::GetBombs()
{
	char PackedID[8] = " ";
	PackedID[0] = 'B';
	static char rtnString[4] = " ";
	sprintf(rtnString, "%d", *(int*)(0x1005194));
	strcat(PackedID, rtnString);
	return PackedID;
}


void ReversedFunctions::SetBombCount(const char* Count)
{
	BYTE BombCount = atoi(Count);
	PatchMem((PVOID)0x1005194, &BombCount, sizeof(BombCount));
	RefreshScreen();
}


const char* ReversedFunctions::GetAllMines()
{
	int count = 1;
	static char rtnString[1024];
	rtnString[0] = 'F';//Kennzeichnung des Pakets mit F fuer Feld (das die Pakete beim Empfangen unterschieden werden koennen)

	for(int i = 0; i < GetFieldHigh(); i++)
	{
		for(int j = 0; j < GetFieldLength(); j++)
		{
			rtnString[count] = GetMine(i, j);
			count++;
		}
	}
	rtnString[count] = '\0';
	return rtnString;
}


void ReversedFunctions::SetAllMines(const char* Mines)
{
	int count = 0;
	for(int i = 1; i <= GetFieldHigh(); i++)
	{
		for(int j = 1; j <= GetFieldLength(); j++)
		{
			SetMine(j, i, (BYTE)Mines[count]);
			count++;
		}
	}
}


void ReversedFunctions::RefreshScreen()
{
	DWORD func = 0x1002801;
	__asm Call func
}


void ReversedFunctions::StartGameFirstTime()
{
	DWORD func = 0x10037E1;
	__asm Call func
}


void ReversedFunctions::FreezeField()
{
	BYTE Patch = 0x10; //dez. 16 -> Freezed die Mausklicks von Spieler -> 1 Unfreezed die Mausklicks wieder
	PatchMem((LPVOID)0x1005000, &Patch, sizeof(Patch));
}


void ReversedFunctions::UnFreezeField()
{
	BYTE Patch = 0x01; //dez. 1 -> UnFreezed die Mausklicks von Spieler -> 1 Unfreezed die Mausklicks wieder
	PatchMem((LPVOID)0x1005000, &Patch, sizeof(Patch));
}


void ReversedFunctions::SetSmiley(const char* Value)
{
	//0 = Laechelnder Smiley, 1 = Smiley mit offenem Mund, 2 = Toder Smiley
	typedef void (__stdcall *pFunctionAddress)(BYTE);
	pFunctionAddress pMySecretFunction = (pFunctionAddress)(0x1002913);
	pMySecretFunction(atoi(Value));
}


int ReversedFunctions::GetSmiley()
{
	return *(int*)(0x1005160);
}


//Liest die Anzahl der bereits aufgedeckten Bomben aus, da es sonst
//am Ende der Runde zu keinem "Gewinn" kommt
const char* ReversedFunctions::GetAmountOpenedMines()
{
	char PackedID[8] = " ";
	PackedID[0] = 'O';
	static char rtnString[4] = " ";
	sprintf(rtnString, "%d\0", *(int*)(0x10057A4));
	strcat(PackedID, rtnString);
	return PackedID;
}


//Setzt die ausgelesenen Bomben des anderen Clients
void ReversedFunctions::SetAmountOpenedMines(const char* Value)
{
	int Amount = atoi(Value);
	PatchMem((PVOID)0x10057A4, &Amount, sizeof(Amount));
}


void ReversedFunctions::CheckGameState()
{
	DWORD func = 0x100347C;
	__asm
	{
		PUSH 1
		CALL func
	}
}


void ReversedFunctions::SetGameState(int State)
{
	printf("\nState: %d", State);
	DWORD Adresse = 0x100347C;
	if(State == 2)
	{
		__asm
		{
			PUSH 0
			CALL Adresse
		}
	}
	else if(State == 3)
	{
		__asm
		{
			PUSH 1
			CALL Adresse
		}
	}
}


int ReversedFunctions::GetFieldLength()
{
	return *(int*)(0x10056AC);
}


void ReversedFunctions::SetFieldLength(BYTE Length)
{
	//Patched die Werte in den Benutzerdef. Einstellungen Hoehe & Breite 
	PatchMem((LPVOID)0x1005334, &Length, sizeof(Length));
	PatchMem((LPVOID)0x10056AC, &Length, sizeof(Length));
	//Ruft die Funktion auf, die das Fenster an die Groesse der Anzahl der Bomben anpasst
	DWORD ResizeField = 0x1001950;
	__asm
	{
		PUSH 6
		CALL ResizeField
	}
}


int ReversedFunctions::GetFieldHigh()
{
	return *(int*)(0x10056A8);
}


void ReversedFunctions::SetFieldHigh(BYTE High)
{
	//Patched die Werte in den Benutzerdef. Einstellungen Hoehe & Breite 
	PatchMem((LPVOID)0x1005338, &High, sizeof(High));
	PatchMem((LPVOID)0x10056A8, &High, sizeof(High));
	//Ruft die Funktion auf, die das Fenster an die Groesse der Anzahl der Bomben anpasst
	DWORD ResizeField = 0x1001950;
	__asm
	{
		PUSH 6
		CALL ResizeField
	}
}


void ReversedFunctions::SetMineCounter(BYTE Counter)
{
	PatchMem((LPVOID)0x10056A4, &Counter, sizeof(Counter));
}

//Gibt Speicher zum Schreiben frei und Schreibt diesen auch gleichzeitig
void ReversedFunctions::PatchMem(LPVOID dwAddress, LPVOID bytes, DWORD dwSize)
{
	DWORD flOldProtect = 0;
	VirtualProtect((void*)dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memcpy((void*) dwAddress, bytes, dwSize);
	VirtualProtect((void*)dwAddress, dwSize, flOldProtect, &flOldProtect);
}


BYTE ReversedFunctions::ReadMem(LPVOID dwAddress, BYTE bytes)
{
	DWORD flOldProtect = 0;
	BYTE ReturnValue;

	VirtualProtect((void*)dwAddress, 1, PAGE_EXECUTE_READWRITE, &flOldProtect);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)dwAddress, &bytes, 1, NULL);
	VirtualProtect((void*)dwAddress, 1, flOldProtect, &flOldProtect);

	return bytes;
}


void ReversedFunctions::ClearField()
{
	for(int i = 1; i <= 24; i++)
	{
		for(int j = 1; j <= 9; j++)
		{
			SetMine(j, i, (BYTE)0x0F);
		}
	}
}


void ReversedFunctions::SetFieldColered(BYTE State)
{
	//0 = Schwarz/Weiss
	//1 = Farbig
	PatchMem((LPVOID)0x10056C8, &State, sizeof(State));
	DWORD func = 0x1002607, func2 = 0x1002414, func3 = 0x1002AF0;
	__asm CALL func
	__asm CALL func2
	__asm CALL func3
}


//Ruft die Funktion zum Disablen des Menu's auf
void ReversedFunctions::DisableMenu()
{
	DWORD func = 0x1003CE5;
	__asm PUSH 1
	__asm CALL func
}