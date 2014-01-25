#include "Network.h"


Network::Network(void)
{
}


Network::~Network(void)
{
}


void Network::Connect()
{
	// Pointers to the interfaces of our server and client.
	// Note we can easily have both in the same program
	client=RakNet::RakPeerInterface::GetInstance();

	// Record the first client that connects to us so we can pass it to the ping function
	clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	// Crude interface
	puts("IP-Adresse des Servers:");
	Gets(ip,sizeof(ip));

	// Holds user data
	//sprintf(ip, "192.168.1.130");
	//ip = "127.0.0.1";
	//serverPort = "1234";
	sprintf(serverPort, "7777");
	//clientPort = "0";
	sprintf(clientPort, "0");

	// A client
	isServer=false;

	RakNet::SocketDescriptor socketDescriptor(atoi(clientPort),0);
	socketDescriptor.socketFamily=AF_INET;
	client->Startup(8,&socketDescriptor, 1);
	client->SetOccasionalPing(true);
	RakNet::ConnectionAttemptResult b = client->Connect(ip, atoi(serverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));
	RakAssert(b==RakNet::CONNECTION_ATTEMPT_STARTED);
}


void Network::CheckIncomingPackets()
{
	ReversedFunctions	User;

	// Get a packet from either the server or the client
	for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive())
	{
		// We got a packet, get the identifier with our handy function
		packetIdentifier = GetPacketIdentifier(p);

		// Check if this is a network message packet
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			// Connection lost normally
			printf("ID_DISCONNECTION_NOTIFICATION\n");
			break;
		case ID_ALREADY_CONNECTED:
			// Connection lost normally
			printf("ID_ALREADY_CONNECTED with guid %d", p->guid);
			break;
		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
			break;
		case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
			printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
			break;
		case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
			printf("ID_REMOTE_CONNECTION_LOST\n");
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
			printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
			break;
		case ID_CONNECTION_BANNED: // Banned from this server
			printf("ID_CONNECTION_BANNED\n");
			break;			
		case ID_CONNECTION_ATTEMPT_FAILED:
			printf("ID_CONNECTION_ATTEMPT_FAILED\n");
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			// Sorry, the server is full.  I don't do anything here but
			printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
			break;

		case ID_INVALID_PASSWORD:
			//printf("ID_INVALID_PASSWORD\n");
			printf("ID_INVALID_PASSWORD\n");
			break;

		case ID_CONNECTION_LOST:
			// Couldn't deliver a reliable packet - i.e. the other system was abnormally
			// terminated
			printf("ID_CONNECTION_LOST\n");
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			// This tells the client they have connected
			printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\nMy external address is %s\n", p->systemAddress.ToString(true), 
				p->guid.ToString(), client->GetExternalID(p->systemAddress).ToString(true));
			//User.RestartGame();
			break;
		case ID_CONNECTED_PING:
		case ID_UNCONNECTED_PING:
			//printf("Ping from %s\n", p->systemAddress.ToString(true));
			printf("ID_UNCONNECTED_PING\n");
			break;
		default:
			// It's a client, so just show the message
			fflush(stdin);
			//printf("%s\n", p->data);
			GetMinePacketIdentifier(p);
			if(User.GetSmiley() != 2 && User.GetSmiley() != 3)
			{
				User.UnFreezeField();
			}
			break;
		}
	}
}


unsigned char Network::GetPacketIdentifier(RakNet::Packet *p)
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


// Paketunterscheidung -> Spielfeld, Zeit oder BombenCounter
unsigned char Network::GetMinePacketIdentifier(RakNet::Packet *p)
{
	ReversedFunctions	User;
	if((unsigned char)p->data[0] == 'F')
	{
		for(int i = 0; p->data[i] != '\0'; i++)
		{
			p->data[i] = p->data[i+1];
		}

		User.SetAllMines((char*)p->data);
		User.SetFieldColered(1);//macht das Feld wieder farbig, dass der Spieler erkennt wann er dran ist
	}
	else if((unsigned char)p->data[0] == 'T')
	{
		for(int i = 0; i < sizeof(p->data); i++)
		{
			p->data[i] = p->data[i+1];
		}
		User.SetTime((char*)p->data);
	}
	else if((unsigned char)p->data[0] == 'B')
	{
		for(int i = 0; i < sizeof(p->data); i++)
		{
			p->data[i] = p->data[i+1];
		}
		User.SetBombCount((char*)p->data);
	}
	else if((unsigned char)p->data[0] == 'S')
	{
		for(int i = 0; i < sizeof(p->data); i++)
		{
			p->data[i] = p->data[i+1];
		}
		//User.SetSmiley((char*)p->data);
		printf("GameState beim Empfang: %d", atoi((char*)p->data));
		User.SetGameState(atoi((char*)p->data));
	}
	else if((unsigned char)p->data[0] == 'O')
	{
		for(int i = 0; i < sizeof(p->data); i++)
		{
			p->data[i] = p->data[i+1];
		}
		User.SetAmountOpenedMines((char*)p->data);
	}
	else if((unsigned char)p->data[0] == 'N')
	{
		printf("\nNeues Spiel gestartet.\n");
		User.SetFieldLength(p->data[1]);
		User.SetFieldHigh(p->data[2]);
		User.SetMineCounter(p->data[3]);
		User.RestartGame();
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; p->data[j] != '\0'; j++)
			{
				p->data[j] = p->data[j+1];
			}
		}

		User.RestartGame2(p->data[2], p->data[1]); //Danach den StartTimer setzen
		User.SetAllMines((char*)p->data); // ERST DANACH! Felder setzen, da die obere StartTimer Funktion diese sonst ueberschreibt
		User.SetTime((char*)"0");
		User.SetFieldColered(1);//macht das Feld wieder farbig, dass der Spieler erkennt wann er dran ist
	}
	return (unsigned char) p->data[0];
}


void Network::SendField()
{
	ReversedFunctions	User;
	char*				Packet = (char*)User.GetAllMines();
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Network::SendTime()
{
	ReversedFunctions	User;
	char*				Packet = (char*)User.GetTime();
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Network::SendBombCount()
{
	ReversedFunctions	User;
	char*				Packet = (char*)User.GetBombs();
	printf("\nGetBombCount() = %s", Packet);
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Network::SendGameState(int State)
{
	char Packet[3];
	sprintf(Packet, "S%d", State);
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Network::SendAmountOpenedMines()
{
	ReversedFunctions	User;
	char*				Packet = (char*)User.GetAmountOpenedMines();
	//printf("\nSendAmountOpenedMInes() = %s", Packet);
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


void Network::SendNewGameRequest()
{
	char*	Packet = "SNGR";
	client->Send(Packet, (int)strlen(Packet)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}