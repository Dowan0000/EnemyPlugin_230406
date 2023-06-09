// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ThreadInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UThreadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENEMYPLUGIN_230406_API IThreadInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CreateThread();
	virtual void CreateThread_Implementation() {};
};
