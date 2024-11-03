#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponHolder.generated.h"

UINTERFACE()
class UWeaponHolder : public UInterface
{
	GENERATED_BODY()
};

class M012237NC_API IWeaponHolder
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateAmmoUI(int CurrentAmmo, int MaxAmmo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChooseWeapon();
};
