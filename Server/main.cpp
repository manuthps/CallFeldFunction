// ----------------------------------------------------------------------
// RakNet version 1.0
// Filename ChatExample.cpp
// Created by Rakkar Software (rakkar@jenkinssoftware.com) January 24, 2003
// Very basic chat engine example
// ----------------------------------------------------------------------

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "Kbhit.h"
#include <stdio.h>
#include <string.h>
#include "Gets.h"

#if LIBCAT_SECURITY==1
#include "SecureHandshake.h" // Include header for secure handshake
#endif

#if defined(_CONSOLE_2)
#include "Console2SampleIncludes.h"
#endif

// We copy this from Multiplayer.cpp to keep things all in one file for this example
unsigned char GetPacketIdentifier(RakNet::Packet *p);

#ifdef _CONSOLE_2
_CONSOLE_2_SetSystemProcessParams
#endif

/*
BYTE SpielFeld[9][9] = {
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
	{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F}
};
*/

int Laenge = 0, Hoehe = 0, Anz_Bomben = 0;
const char* StartNewGame(int Laenge, int Hoehe, int AnzahlBomben);

int main(void)
{
	SetConsoleTitle("Minesweeper-Multiplayer Server by ManU");
	// Pointers to the interfaces of our server and client.
	// Note we can easily have both in the same program
	RakNet::RakPeerInterface *server=RakNet::RakPeerInterface::GetInstance();
	RakNet::RakNetStatistics *rss;
	server->SetIncomingPassword("Rumpelstiltskin", (int)strlen("Rumpelstiltskin"));
	server->SetTimeoutTime(30000,RakNet::UNASSIGNED_SYSTEM_ADDRESS);
//	RakNet::PacketLogger packetLogger;
//	server->AttachPlugin(&packetLogger);

#if LIBCAT_SECURITY==1
	cat::EasyHandshake handshake;
	char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
	char private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];
	handshake.GenerateServerKey(public_key, private_key);
	server->InitializeSecurity(public_key, private_key, false);
	FILE *fp = fopen("publicKey.dat","wb");
	fwrite(public_key,sizeof(public_key),1,fp);
	fclose(fp);
#endif

	// Holds packets
	RakNet::Packet* p;

	// GetPacketIdentifier returns this
	unsigned char packetIdentifier;

	// Record the first client that connects to us so we can pass it to the ping function
	RakNet::SystemAddress clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	// Holds user data
	char portstring[30];

	printf("Minesweeper-Multiplayer by ManU\n\n\n");

	// A server
	puts("Gib den Port fuer den Server an: ");
	Gets(portstring,sizeof(portstring));
	if (portstring[0]==0)
		strcpy(portstring, "7777");
	
	puts("Server wird gestartet...");
	// Starting the server is very simple.  2 players allowed.
	// 0 means we don't care about a connectionValidationInteger, and false
	// for low priority threads
	// I am creating two socketDesciptors, to create two sockets. One using IPV6 and the other IPV4
	RakNet::SocketDescriptor socketDescriptors[2];
	socketDescriptors[0].port=atoi(portstring);
	socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
	socketDescriptors[1].port=atoi(portstring);
	socketDescriptors[1].socketFamily=AF_INET6; // Test out IPV6
	bool b = server->Startup(4, socketDescriptors, 2 )==RakNet::RAKNET_STARTED;
	server->SetMaximumIncomingConnections(4);
	if (!b)
	{
		printf("IPv6 Port konnte nicht gestartet werden. Aufbauversuch nur IPv4...\n");

		// Try again, but leave out IPV6
		b = server->Startup(4, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
		if (!b)
		{
			puts("Server konnte nicht gestartet werden.");
			exit(1);
		}
	}
	server->SetOccasionalPing(true);
	server->SetUnreliableTimeout(1000);

	DataStructures::List< RakNet::RakNetSocket2* > sockets;
	server->GetSockets(sockets);
	/*printf("Socket addresses used by RakNet:\n");
	for (unsigned int i=0; i < sockets.Size(); i++)
	{
		printf("%i. %s\n", i+1, sockets[i]->GetBoundAddress().ToString(true));
	}*/

	printf("\nEigene IP-Adresse:\n");
	for (unsigned int i=0; i < server->GetNumberOfAddresses(); i++)
	{
		RakNet::SystemAddress sa = server->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
		printf("%i. %s (LAN=%i)\n", i+1, sa.ToString(false), sa.IsLANAddress());
	}

	//printf("\nMy GUID is %s\n", server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	puts("Tippe 'newgame' fuer eine neue Runde.");
	char message[2048];

	// Loop for input
	while (1)
	{

	// This sleep keeps RakNet responsive
	RakSleep(30);

	if (kbhit())
	{
		// Notice what is not here: something to keep our network running.  It's
		// fine to block on gets or anything we want
		// Because the network engine was painstakingly written using threads.
		Gets(message,sizeof(message));

		/*if (strcmp(message, "quit")==0)
		{
			puts("Quitting.");
			break;
		}

		if (strcmp(message, "stat")==0)
		{
			rss=server->GetStatistics(server->GetSystemAddressFromIndex(0));
			StatisticsToString(rss, message, 2);
			printf("%s", message);
			printf("Ping %i\n", server->GetAveragePing(server->GetSystemAddressFromIndex(0)));
	
			continue;
		}

		if (strcmp(message, "ping")==0)
		{
			server->Ping(clientID);

			continue;
		}

		if (strcmp(message, "pingip")==0)
		{
			printf("Enter IP: ");
			Gets(message,sizeof(message));
			printf("Enter port: ");
			Gets(portstring,sizeof(portstring));
			if (portstring[0]==0)
				strcpy(portstring, "1234");
			server->Ping(message, atoi(portstring), false);

			continue;
		}

		if (strcmp(message, "kick")==0)
		{
			server->CloseConnection(clientID, true, 0);

			continue;
		}

		if (strcmp(message, "getconnectionlist")==0)
		{
			RakNet::SystemAddress systems[10];
			unsigned short numConnections=10;
			server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
			for (int i=0; i < numConnections; i++)
			{
				printf("%i. %s\n", i+1, systems[i].ToString(true));
			}
			continue;
		}

		if (strcmp(message, "ban")==0)
		{
			printf("Enter IP to ban.  You can use * as a wildcard\n");
			Gets(message,sizeof(message));
			server->AddToBanList(message);
			printf("IP %s added to ban list.\n", message);

			continue;
		}*/

		if (strcmp(message, "newgame")==0)
		{
			printf("\nLaenge des Feldes: ");
			scanf("%d", &Laenge);
			if(Laenge > 30)	{Laenge = 30;}
			printf("\nHoehe des Feldes: ");
			scanf("%d", &Hoehe);
			if(Hoehe > 24)	{Hoehe = 24;}
			printf("\nAnzahl der Bomben: ");
			scanf("%d", &Anz_Bomben);
			char*				Packet = (char*)StartNewGame(Laenge, Hoehe, Anz_Bomben);
			//printf("\nNew Game: %s", Packet);
			char message3[2048];
			message3[0] = 0;
			strcat(message3, Packet);
			server->Send(message3, (int)strlen(message3)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
			continue;
		}


		// Message now holds what we want to broadcast
		char message2[2048];
		// Append Server: to the message so clients know that it ORIGINATED from the server
		// All messages to all clients come from the server either directly or by being
		// relayed from other clients
		message2[0]=0;
		strcpy(message2, "Server: ");
		strcat(message2, message);
	
		// message2 is the data to send
		// strlen(message2)+1 is to send the null terminator
		// HIGH_PRIORITY doesn't actually matter here because we don't use any other priority
		// RELIABLE_ORDERED means make sure the message arrives in the right order
		// We arbitrarily pick 0 for the ordering stream
		// RakNet::UNASSIGNED_SYSTEM_ADDRESS means don't exclude anyone from the broadcast
		// true means broadcast the message to everyone connected
		server->Send(message2, (const int) strlen(message2)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}

		// Get a packet from either the server or the client

		for (p=server->Receive(); p; server->DeallocatePacket(p), p=server->Receive())
		{
			// We got a packet, get the identifier with our handy function
			packetIdentifier = GetPacketIdentifier(p);

			// Check if this is a network message packet
			switch (packetIdentifier)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("ID_DISCONNECTION_NOTIFICATION von %s\n", p->systemAddress.ToString(true));;
				break;


			case ID_NEW_INCOMING_CONNECTION:
				// Somebody connected.  We have their IP now
				printf("ID_NEW_INCOMING_CONNECTION von %s mit GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
				clientID=p->systemAddress; // Record the player ID of the client

				printf("Remote internal IDs:\n");
				for (int index=0; index < MAXIMUM_NUMBER_OF_INTERNAL_IDS; index++)
				{
					RakNet::SystemAddress internalId = server->GetInternalID(p->systemAddress, index);
					if (internalId!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
					{
						printf("%i. %s\n", index+1, internalId.ToString(true));
					}
				}

				break;

			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;

			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
				printf("Ping von %s\n", p->systemAddress.ToString(true));
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST von %s\n", p->systemAddress.ToString(true));;
				break;

			default:
				// The server knows the static data of all clients, so we can prefix the message
				// With the name data
				//printf("%s\n", p->data);

				// Relay the message.  We prefix the name for other clients.  This demonstrates
				// That messages can be changed on the server before being broadcast
				// Sending is the same as before
				sprintf(message, "%s", p->data);
				if(strcmp(message, "SNGR") == 0)
				{
					//printf("\nSNGR");
					char*				PacketSNGR = (char*)StartNewGame(Laenge, Hoehe, Anz_Bomben);
					//printf("\nNew Game: %s", PacketSNGR);
					char message4[2048];
					message4[0] = 0;
					strcat(message4, PacketSNGR);
					server->Send(message4, (int)strlen(message4)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				}
				else
				{
					server->Send(message, (const int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, true);
				}

				break;
			}

		}
	}

	server->Shutdown(300);
	// We're done with the network
	RakNet::RakPeerInterface::DestroyInstance(server);

	return 0;
}

// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}


const char* StartNewGame(int Laenge, int Hoehe, int AnzahlBomben)
{
	int *randX = new int[AnzahlBomben];
	int *randY = new int[AnzahlBomben];
	//BYTE *SpielFeld = new int[Laenge][Breite];

	BYTE ** SpielFeld;
	 /* Speicher reservieren für die int-Zeiger (=zeile) */
	SpielFeld = (BYTE**)malloc(Laenge * sizeof(BYTE *));
	if(NULL == SpielFeld) {
		printf("Kein virtueller RAM mehr vorhanden ... !");
		return 0;
	}
	/* jetzt noch Speicher reservieren für die einzelnen Spalten
	* der i-ten Zeile */
	for(int i = 0; i < Laenge; i++) {
		SpielFeld[i] = (BYTE*)malloc(Hoehe * sizeof(BYTE));
			if(NULL == SpielFeld[i]) {
			printf("Kein Speicher mehr fuer Zeile %d\n",i);
			return 0;
			}
	}

	int ok = 0;
	int i = 0, j = 0;

	//Alle Felder wieder leeren (falls sie vorher schon einmal gefuellt wurden)
	for(i = 0; i < Laenge; i++)
	{
		for(j = 0; j < Hoehe; j++)
		{
			SpielFeld[i][j] = 0x0F;
		}
	}



	//Bomben zufaellig setzen
	for(i = 0; i < AnzahlBomben; i++)
	{
		randX[i] = (0 + ( rand() % Laenge ));
		randY[i] = (0 + ( rand() % Hoehe ));

		while(ok == 0)
		{
			for(j = 0; j < AnzahlBomben; j++)
			{
				if((randX[i] == randX[j]) && (randY[i] == randY[j]) && (i != j))
				{
					randX[i] = (0 + (rand() % Laenge));
					randY[i] = (0 + (rand() % Hoehe));
					j = 0;
				}
				else
				{
					if (j == AnzahlBomben - 1)
					{
						ok = 1;
					}
				}
			}
		}
		SpielFeld[(BYTE)randX[i]][(BYTE)randY[i]] = 0x8F;
		ok = 0;
	}

	/*
	printf("\n");
	for(i = 0; i < Laenge; i++)
	{
		for(j = 0; j < Hoehe; j++)
		{
			printf("%X", SpielFeld[i][j]);
		}
	}
	printf("\n\n\n");*/




	int count = 4;//normal 1
	static char rtnString[2048] = " ";
	rtnString[0] = 'N';//Kennzeichnung des Pakets mit N fuer ein NewGame
	rtnString[1] = Laenge;
	rtnString[2] = Hoehe;
	rtnString[3] = AnzahlBomben;
	//rtnString[1] = (char)0x48;
	//rtnString[2] = (char)0x48;
	//rtnString[3] = (char)0x48;

	//In String auslagern
	for(int i = 0; i < Laenge; i++)
	{
		for(int j = 0; j < Hoehe; j++)
		{
			rtnString[count] = SpielFeld[i][j];
			//printf("%X", SpielFeld[i][j]);
			count++;
		}
		//printf("\n");
	}

	//rtnString[count-1] = (char)0x8F;
	rtnString[count] = '\0';
	//printf("\nCount: %d\nNew Game: %s", count, rtnString);
	delete SpielFeld;
	return rtnString;
}