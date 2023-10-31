// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WHYYCharacter.generated.h"



class UWHYCharacterMovementComponent;

/// <summary>
///  가속도 표현 구조체
/// </summary>

USTRUCT()
struct FWHYReplicatedAccelaration
{
	GENERATED_BODY()

	UPROPERTY()
	uint8 AccelXYRadians = 0;		// 2D 평면에서 가속도 방향을 라디안 단위로 표현하는 변수 즉, 가속도의 방향

	UPROPERTY()
	uint8 AccelXYMagnitude = 0;		// XY 평면에서의 가속도 크기를 나타내는 변수 이 값은 양자화 되어 [0, MaxAcceleration] 범위로 표현

	UPROPERTY()
	int8 AccelZ = 0;				// Z 축(수직 방향)에서의 가속도를 나타내는 변수, 이 값 역시 양자화 되어 [-MaxAcceleration, MaxAcceleration] 범위로 표현
};

USTRUCT()
struct FSharedRepMovement
{
	GENERATED_BODY()

	FSharedRepMovement();

	bool FillForCharacter(ACharacter* Character);
	bool Equals(const FSharedRepMovement& Other, ACharacter* Character) const;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UPROPERTY(Transient)
	FRepMovement RepMovement;

	UPROPERTY(Transient)
	float RepTimeStamp = 0.0f;

	UPROPERTY(Transient)
	uint8 RepMovementMode = 0;

	UPROPERTY(Transient)
	bool bProxyIsJumpForceApplied = false;

	UPROPERTY(Transient)		// Transient = 일시적
	bool bIsCrouched = false;
};

template<>		// TStructOpsTypeTraits 템플릿을 FSharedRepMovement 타입에 대한 특화 구조체로 선언
struct TStructOpsTypeTraits<FSharedRepMovement> : public TStructOpsTypeTraitsBase2<FSharedRepMovement>
{
	enum
	{
		WithNetSerializer = true,			// UnrealEngine은 이 구조체에 대한 네트워크 직렬화를 활성화
		WithNetSharedSerialization = true,	// 이 구조체에 대한 공유 네트워크 직렬화를 활성화
	};
};

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
	// AActor Init
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;		// WHYPawnExtensionComponent에 있음
	virtual void Reset() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// AActor End

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Meta = (AllowPrivateAccess = "true")는 private 변수여도 다른 외부 클래스나 블루프린트에서 접근 할 수 있도록 설정
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WHY|Character", Meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UWHYCharacterMovementComponent> PawnExtComponent;	
};
