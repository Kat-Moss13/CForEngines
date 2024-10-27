
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inputable.h"
#include "P_FPS.generated.h"

class UWeaponType;
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
class UArrowComponent;
class AWeapon_Base;

UCLASS(Abstract)
class M012237NC_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	
	AP_FPS();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement")
	float SprintSpeedMultiplier;

	bool isCrouched;

	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_InteractPressed_Implementation(bool canExit) override;
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;
	virtual void Input_LeanLeftPressed_Implementation() override;
	virtual void Input_LeanLeftReleased_Implementation() override;
	virtual void Input_LeanRightPressed_Implementation() override;
	virtual void Input_LeanRightReleased_Implementation() override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	
	virtual void BeginPlay() override;

	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;
	
protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> _Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponType> _DefaultWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _InteractArrow;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
	
};
