﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UWeaponType;
class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS(Abstract)
class M012237NC_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	AWeapon_Base();

	void Init(UWeaponType* type);

	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;


	void StartFire(AController* causer);
	void StopFire();
	void Reload(AController* causer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void fireSound();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMeshComponent> _Hammer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMeshComponent> _Slide;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMeshComponent> _Mag;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMeshComponent> _Silencer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponType> _TypeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _AmmoClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;


	UFUNCTION()
	virtual void Fire();
};
