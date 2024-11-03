
#include "P_FPS.h"

#include <cmath>

#include "FrameTypes.h"
#include "HealthComponent.h"
#include "Interact.h"
#include "Weapon_Base.h"
#include "WeaponType.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"



AP_FPS::AP_FPS()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_Capsule->SetupAttachment(RootComponent);
	
	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	_InteractArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Interact Arrow"));
	_InteractArrow->SetupAttachment(_Camera);

	SprintSpeedMultiplier = 2;
}
void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);

	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		//_WeaponRef->Init(_DefaultWeaponType);
	}
}

void AP_FPS::Input_ReloadPressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->Reload(this->Controller);
	}
}

void AP_FPS::UpdateWeapon_Implementation(UWeaponType* Weapon)
{
	_WeaponRef->Init(Weapon);
}


UBehaviorTree* AP_FPS::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

void AP_FPS::Input_FirePressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StartFire(this->Controller);
	}
}

void AP_FPS::Input_FireReleased_Implementation()
{
	if(_WeaponRef)
    {
       _WeaponRef->StopFire();
    }
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AP_FPS::Input_Look_Implementation(FVector2D value)
{
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(value.Y, 0.0f, 0.0f));
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);
	
}

void AP_FPS::Input_InteractPressed_Implementation(bool canExit)
{
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
 
	FHitResult hit(ForceInit);
	FVector start = _InteractArrow->GetComponentLocation();
	FVector end = start + (_InteractArrow->GetForwardVector() * 1000);
	TArray<AActor*> ActorsToIgnore;
 
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
	   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
	   ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
	   FLinearColor::Green, 5))
	{

		if(UKismetSystemLibrary::DoesImplementInterface(hit.GetActor(), UInteract::StaticClass()))
		{
			IInteract::Execute_Interact(hit.GetActor(), this->Controller, canExit);
		}
	}
	
}

void AP_FPS::Input_CrouchPressed_Implementation()
{
	isCrouched = true;
	Crouch();
}

void AP_FPS::Input_CrouchReleased_Implementation()
{
	isCrouched = false;
	UnCrouch();
}

void AP_FPS::Input_SprintPressed_Implementation()
{
	if(!isCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
	}
	
}

void AP_FPS::Input_SprintReleased_Implementation()
{
	if(!isCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
		
	}
}

void AP_FPS::Input_LeanLeftPressed_Implementation()
{
	_Camera->AddRelativeRotation(FRotator(0.0f, 0.0f, -30.0f));
	_Camera->SetRelativeLocation(FVector(0.0f, -30.0f, 70.0f));
}

void AP_FPS::Input_LeanLeftReleased_Implementation()
{
	_Camera->AddRelativeRotation(FRotator(0.0f, 0.0f, 30.0f));
	_Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
}

void AP_FPS::Input_LeanRightPressed_Implementation()
{
	_Camera->AddRelativeRotation(FRotator(0.0f, 0.0f, 30.0f));
	_Camera->SetRelativeLocation(FVector(0.0f, 30.0f, 70.0f));
}

void AP_FPS::Input_LeanRightReleased_Implementation()
{
	_Camera->AddRelativeRotation(FRotator(0.0f, 0.0f, -30.0f));
	_Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
}


UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}



void AP_FPS::Handle_HealthDead(AController* causer)
{
	
}

void AP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
	
}



