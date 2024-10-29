#include "Weapon_Base.h"

#include "WeaponType.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshSocket.h"

AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.f;
 
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
 
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Hammer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hammer"));
	_Hammer->SetupAttachment(RootComponent);

	_Slide = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slide"));
	_Slide->SetupAttachment(RootComponent);

	_Mag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag"));
	_Mag->SetupAttachment(RootComponent);

	_Silencer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Silencer"));
	_Silencer->SetupAttachment(RootComponent);
 
	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Root);
	
}

void AWeapon_Base::Init(UWeaponType* type)
{
	_TypeData = type;
	_Mesh->SetStaticMesh(_TypeData->_WeaponMesh);
	_Hammer->SetStaticMesh(_TypeData->_Hammer);
	_Slide->SetStaticMesh(_TypeData->_Slide);
	_Mag->SetStaticMesh(_TypeData->_Mag);
	TArray<UStaticMeshSocket*> Sockets = _TypeData->_WeaponMesh->GetSocketsByTag(TEXT("Muzzle"));

	if(_TypeData->SilencerOn == true)
	{
		_Silencer->SetStaticMesh(_TypeData->_Silencer);
	}
	if(Sockets.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Array Empty"));
	}
	_Muzzle->SetRelativeLocation(Sockets[0]->RelativeLocation);
}



void AWeapon_Base::StartFire()
{
	Fire();
	if(_FireDelay != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::Fire, _FireDelay, true);
	}
}
 
void AWeapon_Base::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}
 
void AWeapon_Base::Fire()
{
	OnFire.Broadcast();
}

