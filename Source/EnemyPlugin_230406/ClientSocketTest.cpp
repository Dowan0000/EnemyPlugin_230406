// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocketTest.h"
#include "Sockets.h"
#include "SocketSubSystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
//#include "MyRunnable.h"

// Sets default values
AClientSocketTest::AClientSocketTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClientSocketTest::BeginPlay()
{
	Super::BeginPlay();

	ConnectSocket();

	//FMyRunnable* MyRunnable = new FMyRunnable();

}

// Called every frame
void AClientSocketTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClientSocketTest::ConnectSocket()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	FString Address(TEXT("127.0.0.1"));
	FIPv4Address IP;
	FIPv4Address::Parse(Address, IP);

	int32 port = 6000;

	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(port);

	bool bConnected = Socket->Connect(*Addr);

	if (bConnected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connected!")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to Connect...")));

		GetWorldTimerManager().SetTimer(SocketConnectTimer, this, &AClientSocketTest::ConnectSocket, 0.1f);
	}
}

void AClientSocketTest::SendMessage(FString Message)
{
	/*int32 BytesRead = 0;
	uint8 Buffer = FCString::Atoi(*Message);

	Socket->Send(&Buffer, sizeof(Buffer), BytesRead);*/

	TArray<uint8> ByteArray;
	FTCHARToUTF8 UTF8String(*Message);
	ByteArray.Append((uint8*)UTF8String.Get(), UTF8String.Length());

	int32 NumByteSent = 0;
	
	Socket->Send(ByteArray.GetData(), ByteArray.Num(), NumByteSent);

}

void AClientSocketTest::RecvMessage()
{
	uint8 Buffer[1024];
	int32 BytesRead = 0;
	if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead))
	{
		FString RecvData = FString((char*)Buffer, BytesRead);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("%s"), *RecvData));
	}
}

