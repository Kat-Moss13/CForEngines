
#include "P_FPS.h"

#include "HealthComponent.h"
#include "Interact.h"
#include "Weapon_Base.h"
#include "WeaponType.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



AP_FPS::AP_FPS()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	_InteractArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Interact Arrow"));
	_InteractArrow->SetupAttachment(_Camera);

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach Point"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	_RightFistBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Fist Box"));
	

	SprintSpeedMultiplier = 2;

	
}

void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);
	_RightFistBoxCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AP_FPS::AP_FPS::OnAttackOverlapBegin);
	_RightFistBoxCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &AP_FPS::AP_FPS::OnAttackOverlapEnd);
	
}

void AP_FPS::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(Controller != UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if(_RightFistBoxCollision)
		{
			FAttachmentTransformRules const Rules{EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false};
			_RightFistBoxCollision->AttachToComponent(GetMesh(), Rules, FName("RightHandSocket"));
		}
	}
	
	if(CanHaveGun)
	{
		if(Controller == UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if(_DefaultWeapon)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;
				spawnParams.Instigator = this;
				_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
				_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		
			}
		}
		else
		{
			if(_DefaultWeapon)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;
				spawnParams.Instigator = this;
				_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, GetMesh()->GetSocketTransform(FName("LeftHandSocket")), spawnParams);
				_WeaponRef->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,(FName("LeftHandSocket")));
		
			}
		}
	}
	
	
}


void AP_FPS::Input_ReloadPressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->Reload(this->Controller);
	}
}

FVector AP_FPS::PawnPosition_Implementation()
{
	return this->GetActorLocation();
}



void AP_FPS::UpdateWeapon_Implementation(UWeaponType* Weapon)
{
	if(CanHaveGun)
	{
		_WeaponRef->Init(Weapon);
	}
	
	
}

void AP_FPS::UpdateAIWeapon_Implementation()
{
	_WeaponRef->Init(_DefaultWeaponType);
	UE_LOG(LogTemp, Warning, TEXT("calling update weapon in pawn"));
}


UBehaviorTree* AP_FPS::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

AAIPatrolPath* AP_FPS::GetPatrolPath_Implementation()
{
	return PatrolPath;
}

void AP_FPS::SetMaxWalkSpeed_Implementation(float speed)
{
	this->GetCharacterMovement()->MaxWalkSpeed = speed;
}

int AP_FPS::MeleeAttack_Implementation()
{
	if(AnimMontage)
	{
		PlayAnimMontage(AnimMontage);
	}
	return 0;
}

void AP_FPS::CallGetWeapon_Implementation()
{
	UpdateAIWeapon_Implementation();
}

UAnimMontage* AP_FPS::GetMontage() const
{
	return AnimMontage;
}

APawn* AP_FPS::GetAIPawn_Implementation()
{
	return this;
}

AP_FPS* AP_FPS::GetSpecificPawn_Implementation()
{
	return this;
}

void AP_FPS::AttackEnd_Implementation()
{
	_RightFistBoxCollision->SetCollisionProfileName("NoCollision");
	_RightFistBoxCollision->SetNotifyRigidBodyCollision(false);
}

void AP_FPS::AttackStart_Implementation()
{
	_RightFistBoxCollision->SetCollisionProfileName("Fist");
	_RightFistBoxCollision->SetNotifyRigidBodyCollision(true);
	
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

AP_FPS* AP_FPS::GetPawn_Implementation()
{
	return this;
}


void AP_FPS::Handle_HealthDead(AController* causer)
{
	if(this->ActorHasTag(FName("AI")))
	{
		Destroy();
		if(CanHaveGun)
		{
			_WeaponRef->Destroy();
		}
		
	}
	else
	{
		OnPlayerDeath.Broadcast();
		UGameplayStatics::OpenLevel(this, "KFM_Map", true);
		                      
	}
	
}

void AP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
	
	OnPawnDamaged.Broadcast(current, max, change);
}

void AP_FPS::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor ==this)
	{
		return;
	}
	if(OtherActor ==UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 5,
		   GetOwner()->GetInstigatorController(), GetOwner(),
		   UDamageType::StaticClass());
	}
}

void AP_FPS::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}




