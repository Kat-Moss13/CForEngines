#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GunSelectionMenu.generated.h"

class UTextBlock;
class UButton;
class UWeaponType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponChangeSignature, UWeaponType* , weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartSignature);

UCLASS(Abstract, BlueprintType)
class M012237NC_API UGunSelectionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	
	bool WeaponSelected = false;

	UPROPERTY(BlueprintAssignable)
	FWeaponChangeSignature OnChangedWeapon;

	UPROPERTY(BlueprintAssignable)
	FGameStartSignature OnStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWeaponType*> _Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponType> _WeaponChosen;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BarettaText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BarettaButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GlockText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GlockButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> M16Text;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> M16Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StartText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void SetBaretta();
	UFUNCTION()
	void SetGlock();
	UFUNCTION()
	void SetM16();
	UFUNCTION()
	void UpdateGunSelection(UWeaponType* weaponChosen);
};

