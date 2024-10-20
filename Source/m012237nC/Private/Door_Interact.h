#pragma once

#include "CoreMinimal.h"
#include "Interact_Parent.h"
#include "Door_Interact.generated.h"

UCLASS()
class M012237NC_API ADoor_Interact : public AInteract_Parent
{
	GENERATED_BODY()

public:

	ADoor_Interact();


	virtual void Interact_Implementation(AController* cause, bool canExit) override;
};

