﻿#include "Weapon_Base.h"

#include "WeaponType.h"
#include "Components/ArrowComponent.h"

AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.f;
 
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
 
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
 
	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Root);
	
}

void AWeapon_Base::Init(UWeaponType* type)
{
	_TypeData = type;
	UE_LOG(LogTemp, Warning, TEXT("mesh %s"), *_TypeData->_WeaponMesh.GetName());
	_Mesh->SetStaticMesh(_TypeData->_WeaponMesh);
	
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
