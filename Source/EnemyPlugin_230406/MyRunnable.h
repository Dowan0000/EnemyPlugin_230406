// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ENEMYPLUGIN_230406_API FMyRunnable : public FRunnable
{
public:
	FMyRunnable();
	~FMyRunnable() override;

	bool Init() override;
	uint32 Run() override;
	void Exit() override;

	FSocket* Socket;

protected:
	void RecvMessage();

private:
	FRunnableThread* Thread;

	FTimerHandle SocketConnectTimer;
};
