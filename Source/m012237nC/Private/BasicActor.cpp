// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicActor.h"

#include "HealthComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ABasicActor::ABasicActor()
{
	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasicActor::BeginPlay()
{
	Super::BeginPlay();

	_Collider->OnComponentHit.AddUniqueDynamic(this, &ABasicActor::Handle_ColliderHit);
}

void ABasicActor::Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}
