// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "NativeGameplayTags.h"



#include "WHYCharacterMovementComponent.generated.h"

class UObject;
struct FFrame;

// 게임플레이 태그를 선언
// PROJECT_WHYY_API는 이 태그를 다른 모듈에서 접근할 수 있도록 함
PROJECT_WHYY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_MovementStopped);

 /**
 * FLyra 문자 접지 정보
 *
 * 캐릭터 밑의 지면에 대한 정보입니다. 필요에 따라서만 업데이트됩니다.
 */
USTRUCT(BlueprintType)
struct FWHYCharacterGroundInfo
{
	// 이 매크로를 사용함으로써 이 구조체를 언리얼 엔진의 시스템과 쉽게 연결 시킬 수 있음
	// 기능
	// - 리플렉션 시스템
	// - 가비지 컬렉션
	// 네트워킹
	GENERATED_BODY()

	// 초기화 리스트 생성자
	FWHYCharacterGroundInfo()
		: LastUpdateFrame(0)
		, GroundDistance(0.0f)
	{}

	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

/**
* UWHY 문자 이동 구성 요소
*
* 이 프로젝트에서 사용하는 기본 문자 이동 구성 요소 클래스입니다.
*/

UCLASS(Config = Game)
class PROJECT_WHYY_API UWHYCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UWHYCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void SimulateMovement(float DeltaTime) override;

	virtual bool CanAttemptJump() const override;

	// 현재 Ground 정보를 반환
	UFUNCTION(BlueprintCallable, Category = "WHYY|CharacterMovement")
	const FWHYCharacterGroundInfo& GetGroundInfo();

	// InAceeleration값이 변하지 않기 위해 const로 받아옴
	// 그렇기에 InAcceleration이라는 매개변수는 읽기전용이다.
	// 참조로 전달하는 이유는 복사를 수행하지 않으므로 메모리 사용을 줄일 수 있음
	// 예기치 않은 수정방지를 위해
	void SetReplicatedAcceleration(const FVector& InAcceleration);

	// Get함수이기에 const로 읽기전용으로만 만듬
	virtual FRotator GetDeltaRotation(float DeltaTime) const override;
	virtual float GetMaxSpeed() const override;

protected:

	virtual void InitializeComponent() override;


protected:
	// 캐릭터에 대한 캐시된 그라운드 정보입니다. 직접 액세스하지 마십시오! GetGroundInfo()를 통해 액세스할 때만 업데이트됩니다.
	FWHYCharacterGroundInfo CachedGroundInfo;

	// 이 매크로는 수명주기를 나타내는 플래그
	// 즉, 게임을 저장하거나 로드할 때 이 변수의 값은 저장되거나 복원되지 않음
	UPROPERTY(Transient)
	bool bHasReplicatedAcceleration = false;
};
