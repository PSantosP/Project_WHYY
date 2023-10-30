// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WHYYCharacter.generated.h"

// Game.ini에서 설정을 불러오는 것으로 가능
// 툴팁 설정
// 아래 매크로 설명
UCLASS(Config = Game, Meta = (ShortTolltip = "기본 Pawn클래스를 상속하는 클래스"))
class PROJECT_WHYY_API AWHYYCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWHYYCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
