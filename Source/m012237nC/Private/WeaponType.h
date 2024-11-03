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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _Hammer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _Slide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _Mag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _Silencer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SilencerOn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _MaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _AmmoClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
};
