// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "WHYPawnExtensionComponent.generated.h"

namespace EEndPlayReason { enum Type : int; }

/**
 * 
 */
UCLASS()
class PROJECT_WHYY_API UWHYPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

	UWHYPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	static const FName NAME_ActorFeatureName;
	

protected:

	//UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "WHYY|Pawn")
	//TObjectPtr<const UWHYPAWN
};
