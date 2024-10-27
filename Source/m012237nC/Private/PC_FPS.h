
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Scorable.h"
#include "GameFramework/PlayerController.h"
#include "PC_FPS.generated.h"

struct FInputActionValue;
class UInputAction;
class UWidget_HUD;


UCLASS()
class M012237NC_API APC_FPS : public APlayerController , public IScorable
{

	GENERATED_BODY()

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

	int _PlayerPoints;
	bool _CanExit = false;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void AddScore_Implementation(int points) override;
	virtual void ExitTrue_Implementation() override;

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

	virtual void OnPossess(APawn* InPawn) override;

};
