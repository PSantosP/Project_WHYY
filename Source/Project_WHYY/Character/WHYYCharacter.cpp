// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WHYYCharacter.h"

#include "WHYCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net\UnrealNetwork.h"


static FName NAME_WhyCharacterCollisionProfile_Capsule(TEXT("WHYYPawnCapsule"));
static FName NAME_WhyCharacterCollisionProfile_Mesh(TEXT("WHYYPawnMesh"));

// Sets default values
AWHYYCharacter::AWHYYCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWHYCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Super(ObjectInitializer.SetDefaultSubobjectClass<UWHYCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
	// 부모 클래스의 생성자를 호출하는데
	// SetDefaultSubojbectClass 함수를 사용하여
	// 캐릭터의 움직임 컴포넌트로 'UWHYCharacterMovementComponent' 클래스를 설정한다
	// 캐릭터 컴포넌트의 커스터마이즈를 하기위해서 이렇게 설정
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	CapsuleComp->SetCollisionProfileName(NAME_WhyCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// CastCheckd 함수는 주로 안전성 검사를 수행하면서 캐스트 작업을 수행
	// 예기치 않은 상황에서 프로그램이 종료되는 것을 방지하기 위해사용
	// 이 함수를 사용하면 런탕미 중 발생할 수 있는 캐스트 관련 오류를 미리 확인하고 대처 가능
	UWHYCharacterMovementComponent* WHYMoveComp = CastChecked<UWHYCharacterMovementComponent>(GetCharacterMovement());
	WHYMoveComp->GravityScale = 1.0f;
	WHYMoveComp->MaxAcceleration = 2400.0f;
	WHYMoveComp->BrakingFrictionFactor = 1.0f;						// 속도 감소나 멈춤과 관련된 마찰(Friction) 계수를 나타내는 변수, 1.0f면 마찰을 적용하지 않음
	WHYMoveComp->BrakingFriction = 6.0f;							// 브레이크 시 발생하는 마찰을 6.0f으로 설정
	WHYMoveComp->GroundFriction = 8.0f;								// 땅에서의 마찰을 8.0으로 설정 움직일 때 발생하는 마찰
	WHYMoveComp->BrakingDecelerationWalking = 1400.0f;				// 걷는 동안의 브레이크 감속도를 1400으로 설정
	WHYMoveComp->bUseControllerDesiredRotation = false;				// 컨트롤러의 원하는 회전을 사용하지 않도록 설정
	WHYMoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;		// 캐릭터가 움직이면서 웅크리기를 할 수 있도록 설정
	WHYMoveComp->bCanWalkOffLedgesWhenCrouching = true;				// 웅크린 상태에서 경사면에서 내려올 수 있도록 설정
	WHYMoveComp->SetCrouchedHalfHeight(65.0f);						// 웅크렸을 때 캐릭터의 반 높이를 65.0f로 설정

	// TODO : PawnExtComponent 클래스 생성 후
	//PawnExtComponent = CreateDefaultSubobject<UWHYCharacterMovementComponent>(TEXT("PawnExtensionComponent"));
	//PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall

	// TODO : HealthComponent 클래스 생성 후

	// TODO : CameraComponent 클래스 생성 후


	bUseControllerRotationPitch = false;	// 캐릭터 X축 회전 false
	bUseControllerRotationYaw = true;		// 캐릭터 Y축 회전 true
	bUseControllerRotationRoll = false;		// 캐릭터 Z축 회전 false

	BaseEyeHeight = 80.0f;					// 캐릭터 눈 높이 80.0f
	CrouchedEyeHeight = 50.0f;				// 캐릭터 앉을 때 눈 높이 50.f
}

void AWHYYCharacter::PreInitializeComponents()
{
	// 컴포넌트 초기화 하기전 상태
	Super::PreInitializeComponents();
}

// Called when the game starts or when spawned
void AWHYYCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	//const bool bRegisterWithSignificanceManager = !IsNetMode(NM_DedicatedServer);
	//if (bRegisterWithSignificanceManager)
	//{
	//	if ()
	//}
	//
}

void AWHYYCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AWHYYCharacter::Reset()
{
}

void AWHYYCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// TODO
	//DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAcceleration, COND_SimulatedOnly);
}



// Called every frame
void AWHYYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWHYYCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FSharedRepMovement::FSharedRepMovement()
{
}

bool FSharedRepMovement::FillForCharacter(ACharacter* Character)
{
	return false;
}

bool FSharedRepMovement::Equals(const FSharedRepMovement& Other, ACharacter* Character) const
{
	return false;
}

bool FSharedRepMovement::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return false;
}
