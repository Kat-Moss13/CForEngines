﻿#pragma once
 
#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Hitscan.generated.h"
 
UCLASS(Abstract)
class M012237NC_API AWeapon_Hitscan : public AWeapon_Base
{
	GENERATED_BODY()
 
public:
	virtual void Fire() override;
 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;
};