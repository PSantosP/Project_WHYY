// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WHYPawn.h"

// Sets default values
AWHYPawn::AWHYPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AWHYPawn::PreInitializeComponents()
{
}

void AWHYPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AWHYPawn::PossessedBy(AController* NewController)
{
}

void AWHYPawn::UnPossessed()
{
}



// Called every frame
void AWHYPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWHYPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

