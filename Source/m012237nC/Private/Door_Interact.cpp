#include "Door_Interact.h"


ADoor_Interact::ADoor_Interact()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADoor_Interact::Interact_Implementation(AController* causer, bool canExit)
{
	Super::Interact_Implementation(causer, canExit);
	if (canExit)
	{
		OnSuccess.Broadcast(causer);
	}
}
