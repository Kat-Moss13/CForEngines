#include "TreasureParent.h"

#include "TreasureComponent.h"
#include "Components/SphereComponent.h"


ATreasureParent::ATreasureParent()
{
	
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Treasure = CreateDefaultSubobject<UTreasureComponent>(TEXT("Treasure"));
}


