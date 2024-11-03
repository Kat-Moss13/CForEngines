// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "UObject/Interface.h"
#include "ChangeWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UChangeWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class M012237NC_API IChangeWeapon
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateWeapon(UWeaponType* Weapon);
};
