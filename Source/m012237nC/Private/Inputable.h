
#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Inputable.generated.h"

class AP_FPS;
class AAIPatrolPath;
class UBehaviorTree;

UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};

class UInputMappingContext;

class M012237NC_API IInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Look(FVector2D value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FirePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FireReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_InteractPressed(bool canExit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_LeanLeftPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_LeanRightPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_LeanLeftReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_LeanRightReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_ReloadPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_ReloadUIUpdate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AI_SightUpdate(AActor* SeenActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector PawnPosition();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBehaviorTree* GetBehaviorTree();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AAIPatrolPath* GetPatrolPath();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetMaxWalkSpeed(float speed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AP_FPS* GetPawn();
	
};
