#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponType.generated.h"


UCLASS(BlueprintType)
class M012237NC_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _WeaponMesh;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	float _Damage;
};
