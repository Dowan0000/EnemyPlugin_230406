// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRunnable.h"
#include "Sockets.h"
#include "SocketSubSystem.h"
#include "Interfaces/IPv4/IPv4Address.h"

FMyRunnable::FMyRunnable()
{
	Thread = FRunnableThread::Create(this, TEXT("Network Thread"));
}

FMyRunnable::~FMyRunnable()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
		Thread->Kill();
		delete Thread;
	}
}

bool FMyRunnable::Init()
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
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to Connect...")));
		return false;
	}
}

uint32 FMyRunnable::Run()
{
	while (true)
	{
		uint8 Buffer[1024];
		int32 BytesRead = 0;
		if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead))
		{
			FString RecvData = FString((char*)Buffer, BytesRead);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("%s"), *RecvData));
		}
	}
	
	return uint32();
}

void FMyRunnable::Exit()
{
}
