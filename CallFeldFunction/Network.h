#pragma once

#include "RakNet\Source\MessageIdentifiers.h"

#include "RakNet\Source\RakPeerInterface.h"
#include "RakNet\Source\RakNetStatistics.h"
#include "RakNet\Source\RakNetTypes.h"
#include "RakNet\Source\BitStream.h"
#include "RakNet\Source\PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNet\Source\RakNetTypes.h"
#ifdef _WIN32
#include "RakNet\Source\Kbhit.h"
#include "RakNet\Source\WindowsIncludes.h" // Sleep
#else
#include "Kbhit.h"
#include <unistd.h> // usleep
#endif
#include "RakNet\Source\Gets.h"

#include "ReversedFunctions.h"



class Network
{
public:
	Network(void);
	~Network(void);

	void Connect();

	RakNet::RakPeerInterface *client;
	RakNet::Packet* p;

	unsigned char packetIdentifier;
	bool isServer;

	RakNet::SystemAddress clientID;
	char ip[64], serverPort[30], clientPort[30];


	// Ueberprueft alle eingehenden Pakete vom Server
	void CheckIncomingPackets();
	// We copy this from Multiplayer.cpp to keep things all in one file for this example
	unsigned char GetPacketIdentifier(RakNet::Packet *p);
	unsigned char GetMinePacketIdentifier(RakNet::Packet *p);

	void SendField();
	void SendTime();
	void SendBombCount();
	void SendGameState(int State);
	void SendAmountOpenedMines();
	void SendNewGameRequest();
};

