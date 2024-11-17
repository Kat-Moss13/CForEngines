#include "Weapon_Base.h"

#include "WeaponHolder.h"
#include "WeaponType.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"

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
	_Muzzle->SetupAttachment(RootComponent);
	
}

void AWeapon_Base::Init(UWeaponType* type)
{
	if(type)
	{
		UE_LOG(LogTemp, Warning, TEXT("got to init"));
		_TypeData = type;
		_Mesh->SetStaticMesh(_TypeData->_WeaponMesh);
		_Hammer->SetStaticMesh(_TypeData->_Hammer);
		_Slide->SetStaticMesh(_TypeData->_Slide);
		_Mag->SetStaticMesh(_TypeData->_Mag);
		_Mesh->SetWorldScale3D(_TypeData->_Scalar);
		_Hammer->SetWorldScale3D(_TypeData->_Scalar);
		_Slide->SetWorldScale3D(_TypeData->_Scalar);
		_Mag->SetWorldScale3D(_TypeData->_Scalar);
		_Silencer->SetWorldScale3D(_TypeData->_Scalar);

		if(_TypeData->SilencerOn == true)
		{
			_Silencer->SetStaticMesh(_TypeData->_Silencer);
			
		}
		TArray<UStaticMeshSocket*> Sockets = _TypeData->_WeaponMesh->GetSocketsByTag(TEXT("Muzzle"));
		if(Sockets.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket Array Empty"));
		}
		
		_Muzzle->SetRelativeLocation(Sockets[0]->RelativeLocation/(_TypeData->_Scalar.X*10));
		
		_FireDelay = _TypeData->_FireDelay;
		_MaxAmmo = _TypeData->_MaxAmmo;
		_AmmoClip = _TypeData->_AmmoClip;
		_CurrentAmmo = 0;
	}
	
	
}


void AWeapon_Base::StartFire(AController* causer)
{
	if(GetWorld())
	{
		if(_CurrentAmmo > 0)
		{
			_CurrentAmmo--;
			if(UKismetSystemLibrary::DoesImplementInterface(causer, UWeaponHolder::StaticClass()))
			{
				IWeaponHolder::Execute_UpdateAmmoUI(causer, _CurrentAmmo, _MaxAmmo);
			}
			Fire();
			if(_FireDelay != 0.f)
			{
				GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::Fire, _FireDelay, true);
			}
		}
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

void AWeapon_Base::Reload(AController* causer)
{
	if(_MaxAmmo > 0)
	{
		int NeededAmmo = _AmmoClip - _CurrentAmmo;
		if(NeededAmmo > 0)
		{
			if(NeededAmmo >= _MaxAmmo)
			{
				_CurrentAmmo += _MaxAmmo;
				_MaxAmmo = 0;
			}
			else
			{
				_CurrentAmmo += NeededAmmo;
				_MaxAmmo -= NeededAmmo;
			}
		}
	}

	
	
	
	if(UKismetSystemLibrary::DoesImplementInterface(causer, UWeaponHolder::StaticClass()))
	{
		IWeaponHolder::Execute_UpdateAmmoUI(causer, _CurrentAmmo, _MaxAmmo);
	}
}

