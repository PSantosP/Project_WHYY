// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WHYCharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(WHYCharacterMovementComponent)

//UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_MovementStopped, "Gameplay.MovementStopped");

namespace WHYYCharacter
{
	static float GroundTraceDistance = 100000.0f;
	// 콘솔 변수를 자동으로 등록하고 관리하는 클래스
	// 이 변수는 치트코드로 사용할 수 있게 사용
	FAutoConsoleVariableRef CVar_GroundTraceDistance(TEXT("WHYYCharacter.GroundTraceDistance"), GroundTraceDistance,
													 TEXT("Distance to trace down when generating ground information."),
													 ECVF_Cheat);
}

UWHYCharacterMovementComponent::UWHYCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 여기서 CDO 프로퍼티를 초기화 시킨다.
	// CDO란?
	// Class Default Object
	// 언리얼 오브젝트를 생성할 때마다 매번 초기화 시키지 않고,
	// 기본 인스턴스를 미리 만들어 놓고 복제하는 방식으로 메커니즘이 구성되어 있다.

}

void UWHYCharacterMovementComponent::SimulateMovement(float DeltaTime)
{
	if (bHasReplicatedAcceleration)
	{
		const FVector OriginalAcceleration = Acceleration;
		/*Super::SimulateMovement(DeltaTime);*/
		Acceleration = OriginalAcceleration;
	}
	else
	{
		/*Super::SimulateMovement(DeltaTime);*/
	}
}

bool UWHYCharacterMovementComponent::CanAttemptJump() const
{
	return false;
}
