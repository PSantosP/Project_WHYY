// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "GenericTeamAgentInterface.h"
#include "GameFramework/Pawn.h"

#include "WHYPawn.generated.h"

UCLASS()
class PROJECT_WHYY_API AWHYPawn : public APawn/*, public IGenericTeamAgentInterface*/
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWHYPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// AActor Init
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// AActor End

	// APawn Init
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	// APawn End
	
	// IWHYTeamAgentInterface interface
	// TODO
	// End of IWHYTeamAgentInterface interface

protected:
	//virtual FGenericTeamId DetermineNewTeamAfterPossessionEnds(FgenericTeamId OldTeamID) const
	//{
	//	return FGenricTeamId::NoTeam
	//}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
