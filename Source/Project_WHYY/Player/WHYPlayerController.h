// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WHYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_WHYY_API AWHYPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWHYPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// UFUNCTION(BlueprintCallable, Category = "WHY|PlayerController")
	// TODO AWHYPlayerState

	
};
