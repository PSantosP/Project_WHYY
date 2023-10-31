// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WHYCharacterMovementComponent.h"


#include "AbilitySystemComponent.h"			//UAbilitySystemComponent를 사용하기위해
#include "AbilitySystemGlobals.h"			//UAbilitySystemGlobals를 사용하기위해
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(WHYCharacterMovementComponent)

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_MovementStopped, "Gameplay.MovementStopped");

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
		Super::SimulateMovement(DeltaTime);
		Acceleration = OriginalAcceleration;
	}
	else
	{
		Super::SimulateMovement(DeltaTime);
	}
}

bool UWHYCharacterMovementComponent::CanAttemptJump() const
{
	// UCharacterMovementComponent의 구현과 동일하지만 crouch체크가 없다
	// 두 번 점프하고 0이 아닌 점프 홀드 시간에 대한 falling이 포함 되지만, 캐릭터를 검증한다.
	return IsJumpAllowed() &&
		(IsMovingOnGround() || IsFalling());
}

void UWHYCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


const FWHYCharacterGroundInfo& UWHYCharacterMovementComponent::GetGroundInfo()
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (CharacterOwner || (GFrameCounter == CachedGroundInfo.LastUpdateFrame))
	{
		return CachedGroundInfo;
	}

	if (MovementMode == MOVE_Walking)
	{
		CachedGroundInfo.GroundHitResult = CurrentFloor.HitResult;
		CachedGroundInfo.GroundDistance = 0.0f;
	}
	else
	{
		const UCapsuleComponent* CapsuleComp = CharacterOwner->GetCapsuleComponent();
		check(CapsuleComp);		// check매크로 -> CapsuleComp가 참이면 진행 거짓이면 프로그램 중단 후 오류메시지 출력
								// 유효하지 않은 포인터나 예상치 못한 상태에서 계속 실행되는 것을 방지
		const float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();		//  지면을 감지하기 위한 캡슐 콜리전 컴포넌트의 반 높이를 구함
		// 콜리전 채널 정의 UpdatedComponent가 참이면 GetCollisionObjectType을 사용 즉 해당 콜리전의 채널을 사용
		// 그게 아니면 ECC_Pawn 콜리전 채널을 사용
		const ECollisionChannel  CollisionChannel = (UpdatedComponent ? UpdatedComponent->GetCollisionObjectType() : ECC_Pawn);	
		const FVector TraceStart(GetActorLocation());
		// 현재 Z좌표에서 GroundTraceDistance와 CapsuleHalfHeight를 빼서 계산
		// 이로써 캐릭터 아래의 지면과의 교차점을 찾음
		const FVector TraceEnd(TraceStart.X, TraceStart.Y, (TraceStart.Z - WHYYCharacter::GroundTraceDistance - CapsuleHalfHeight));

		// 충돌 쿼리 파라미터를 설정
		// 1. SCENE_QUERY_STAT'매크로를 사용하여 쿼리의 이름을 설정
		// 2. 쿼리를 비충돌 쿼리로 만들기 위해 false로 설정
		// 3. 캐릭터
		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(WHYCharacterMovementComponent_GetGroundInfo), false, CharacterOwner);
		// 충돌 응답 파라미터를 초기화
		FCollisionResponseParams ResponseParam;
		InitCollisionParams(QueryParams, ResponseParam);
		
		// 충돌 결과를 저장할 구조체
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, QueryParams, ResponseParam);

		CachedGroundInfo.GroundHitResult = HitResult;
		CachedGroundInfo.GroundDistance = WHYYCharacter::GroundTraceDistance;

		// 캐릭터의 이동모드가 MOVE_NavWalking인 경우
		// 네비게이션 시스템과 충돌 검사를 수행하면 움직이는 상태
		if (MovementMode == MOVE_NavWalking)
		{
			CachedGroundInfo.GroundDistance = 0.0f;
		}
		else if (HitResult.bBlockingHit)		// 지면과 충돌했을 경우
		{
			CachedGroundInfo.GroundDistance = FMath::Max((HitResult.Distance - CapsuleHalfHeight), 0.0f);
		}
	}

	// UnrealEngine의 내부 프레임 카운터 변수 저장
	CachedGroundInfo.LastUpdateFrame = GFrameCounter;

	return CachedGroundInfo;
}

void UWHYCharacterMovementComponent::SetReplicatedAcceleration(const FVector& InAcceleration)
{
	bHasReplicatedAcceleration = true;
	Acceleration = InAcceleration;
}

FRotator UWHYCharacterMovementComponent::GetDeltaRotation(float DeltaTime) const
{
	// AbilitySystem을 사용하기 위해선 GamePlayAbilities라는 플러그인을 설치해야함
	// 현재 GetOwner()의 UAbilitySystemComponent를 가져옴
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		// 해당 AbilitySystemCopmonent가 "TAG_Gameplay_MovementStopped" 태그를 가지고 있는지 확인
		// 만약 해당 태그가 존재한다면 FRotator(0, 0, 0)을 반환
		// 이렇게 사용하는 이유는 캐릭터의 움직임이 정지되었을 때 특정 동작을 수행하기 위해 사용
		if (ASC->HasMatchingGameplayTag(TAG_Gameplay_MovementStopped))
		{
			return FRotator(0, 0, 0);
		}
	}
	return Super::GetDeltaRotation(DeltaTime);
}

float UWHYCharacterMovementComponent::GetMaxSpeed() const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (ASC->HasMatchingGameplayTag(TAG_Gameplay_MovementStopped))
		{
			return 0;
		}
	}
	return Super::GetMaxSpeed();
}

