#include "TreasureComponent.h"

#include "GameRule_Treasure.h"
#include "Components/SphereComponent.h"


UTreasureComponent::UTreasureComponent()
{
	_TreasureValue = 1;
}



void UTreasureComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_Collider = owner->FindComponentByClass<USphereComponent>();
	if(_Collider == nullptr)
	{
		_Collider = NewObject<USphereComponent>(owner, TEXT("Collider"));
		owner->AddInstanceComponent(_Collider);
		_Collider->RegisterComponent();
		owner->Modify();
	}

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &UTreasureComponent::Handle_PickedUp);

	UGameRule_Treasure::OnRequestTreasures.AddUniqueDynamic(this, &UTreasureComponent::Handle_GameRuleRequestTreasure);
	onTreasureRegistered.Broadcast(this);
	
	 
}

void UTreasureComponent::Handle_PickedUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Handle_TreasureDestroyed(this, OtherActor->GetInstigatorController(), _TreasureValue);
}



void UTreasureComponent::Handle_GameRuleRequestTreasure()
{
	
}

void UTreasureComponent::Handle_TreasureDestroyed(UTreasureComponent* target, AController* causer, int treasureValue)
{
	
	onPickedUp.Broadcast(this,causer, treasureValue);
	GetOwner()->Destroy();
}




