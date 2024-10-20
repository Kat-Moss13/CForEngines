
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

// This class does not need to be modified.
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
	UInputMappingContext* GetMappingContext();
	
};
