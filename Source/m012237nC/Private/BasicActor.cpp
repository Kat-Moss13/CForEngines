// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicActor.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/RotatingMovementComponent.h"


ABasicActor::ABasicActor()
{

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	_RotatingMovement->SetUpdatedComponent(_Root);
}


