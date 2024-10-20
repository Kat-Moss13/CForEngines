#include "GameRule_Treasure.h"

#include "TreasureComponent.h"


UGameRule_Treasure::UGameRule_Treasure()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UGameRule_Treasure::Init()
{
	Super::Init();
	UTreasureComponent::onTreasureRegistered.AddUniqueDynamic(this, &UGameRule_Treasure::UGameRule_Treasure::Handle_TreasureRegistered);
	OnRequestTreasures.Broadcast();
}

void UGameRule_Treasure::Handle_TreasureRegistered(UTreasureComponent* treasure)
{
	if(_Treasures.Contains(treasure)) {return;}
	_Treasures.Add(treasure);
	treasure->onPickedUp.AddUniqueDynamic(this, &UGameRule_Treasure::Handle_TreasureRemoved);
}

void UGameRule_Treasure::Handle_TreasureRemoved(UTreasureComponent* treasure , AController* causer, int treasureValue)
{
	_Treasures.Remove(treasure);
	_AmountRemaining--;
	_NeededTreasure -= treasureValue;
	BroadcastPointsScores(causer, treasureValue);
	if(_NeededTreasure <= 0)
	{
		BroadcastComplete(causer);
	}
}


