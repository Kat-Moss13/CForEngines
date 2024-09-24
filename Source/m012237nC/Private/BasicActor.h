// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicActor.generated.h"

class UArrowComponent;

UCLASS(Abstract)
class M012237NC_API ABasicActor : public AActor
{
	GENERATED_BODY()

public:
	
	ABasicActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
};
