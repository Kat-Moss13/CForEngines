// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicActor.generated.h"

class URotatingMovementComponent;
class UArrowComponent;

UCLASS(Abstract)
class M012237NC_API ABasicActor : public AActor
{
	GENERATED_BODY()

public:
	
	ABasicActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<URotatingMovementComponent> _RotatingMovement;
};
