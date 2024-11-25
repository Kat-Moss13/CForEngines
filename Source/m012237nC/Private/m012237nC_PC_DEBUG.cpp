// Fill out your copyright notice in the Description page of Project Settings.


#include "m012237nC_PC_DEBUG.h"
#include "EnhancedInputComponent.h"

void Am012237nC_PC_DEBUG::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(_DebugAction, ETriggerEvent::Triggered, this, &Am012237nC_PC_DEBUG::Debug);
	}
}


void Am012237nC_PC_DEBUG::Debug(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Debug working"));
}
