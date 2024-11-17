
#pragma once

#include "CoreMinimal.h"
#include "ChangeWeapon.h"
#include "Combat.h"
#include "GameFramework/Character.h"
#include "Inputable.h"
#include "P_FPS.generated.h"

class UBoxComponent;
class UWeaponType;
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
class UArrowComponent;
class AWeapon_Base;
class AAIPatrolPath;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedPawnSignature, float, newHealth, float, maxHealth, float, change);
UCLASS(Abstract)
class M012237NC_API AP_FPS : public ACharacter, public IInputable, public IChangeWeapon, public ICombat
{
	GENERATED_BODY()

public:
	
	AP_FPS();

	UPROPERTY(BlueprintAssignable)
	FHealthDamagedPawnSignature OnPawnDamaged;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement")
	float SprintSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	bool CanHaveGun;
	
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
	virtual void Input_ReloadPressed_Implementation() override;
	virtual FVector PawnPosition_Implementation() override;

	virtual void UpdateWeapon_Implementation(UWeaponType* Weapon) override;
	virtual void UpdateAIWeapon_Implementation() override;
	
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	virtual AP_FPS* GetPawn_Implementation() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;

	virtual AAIPatrolPath* GetPatrolPath_Implementation() override;
	virtual void SetMaxWalkSpeed_Implementation(float speed) override;

	virtual int MeleeAttack_Implementation() override;

	virtual void CallGetWeapon_Implementation() override;

	UAnimMontage* GetMontage() const;
	virtual APawn* GetAIPawn_Implementation() override;
	virtual AP_FPS* GetSpecificPawn_Implementation() override;

	virtual void AttackEnd_Implementation() override;
	virtual void AttackStart_Implementation() override;
	
protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> _Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	UPROPERTY(EDITAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponType> _DefaultWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _InteractArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* _RightFistBoxCollision;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	AAIPatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage;
	
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	
};
