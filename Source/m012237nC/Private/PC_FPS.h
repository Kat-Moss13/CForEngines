#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "InputActionValue.h"
#include "Scorable.h"
#include "WeaponHolder.h"
#include "GameFramework/PlayerController.h"
#include "PC_FPS.generated.h"

class UWidget_WinScreen;
class UWeaponType;
class UGunSelectionMenu;
struct FInputActionValue;
class UInputAction;
class UWidget_HUD;
class AP_FPS;

UCLASS()
class M012237NC_API APC_FPS : public APlayerController, public IScorable, public IWeaponHolder,
                              public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _FireAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _InteractAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _CrouchAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SprintAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LeanLeftAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LeanRightAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _Reload;

	int _PlayerPoints;
	bool _CanExit = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AP_FPS> _PlayerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGunSelectionMenu> _GunWidgetClass;
	TObjectPtr<UGunSelectionMenu> _GunWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_WinScreen> _WinWidgetClass;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidget_WinScreen> _WinWidget;


	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void AddScore_Implementation(int points) override;

	virtual void ExitTrue_Implementation() override;
	virtual void UpdateAmmoUI_Implementation(int CurrentAmmo, int MaxAmmo) override;
	virtual void ChooseWeapon_Implementation() override;
	virtual void FinishGame_Implementation() override;

	void Look(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void JumpPressed();
	void JumpReleased();
	void FirePressed();
	void FireReleased();
	void InteractPressed();
	void CrouchPressed();
	void CrouchReleased();
	void SprintPressed();
	void SprintReleased();
	void LeanLeftPressed();
	void LeanRightPressed();
	void LeanLeftReleased();
	void LeanRightReleased();
	void ReloadPressed();

private:
	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void ChangeWeapon(UWeaponType* Weapon);

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void UpdateHealth(float newHealth, float maxHealth, float change);
};
