#include "Interact_Parent.h"

#include "Components/BoxComponent.h"


AInteract_Parent::AInteract_Parent()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
}
