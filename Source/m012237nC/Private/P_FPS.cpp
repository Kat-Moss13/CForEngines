﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "P_FPS.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AP_FPS::AP_FPS()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_Capsule->SetupAttachment(RootComponent);
}
void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);
	
}

void AP_FPS::Input_FirePressed_Implementation()
{
	//TODO: make it fire
}

void AP_FPS::Input_FireReleased_Implementation()
{
	//TODO: stop firing
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AP_FPS::Input_Look_Implementation(FVector2D value)
{
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(value.Y, 0.0f, 0.0f));
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);
	
}

UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}



void AP_FPS::Handle_HealthDead(AController* causer)
{
}

void AP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
}


