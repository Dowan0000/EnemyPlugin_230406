// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClientSocketTest.generated.h"

UCLASS()
class ENEMYPLUGIN_230406_API AClientSocketTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClientSocketTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void ConnectSocket();

	UFUNCTION(BlueprintCallable)
	void SendMessage(FString Message);

	void RecvMessage();

private:
	FSocket* Socket;

	FTimerHandle SocketConnectTimer;

};
