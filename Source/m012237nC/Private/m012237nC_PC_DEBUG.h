// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "m012237nC_PC_DEBUG.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class M012237NC_API Am012237nC_PC_DEBUG : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _DebugAction;

	virtual void SetupInputComponent() override;

	void Debug(const FInputActionValue& Value);
};
