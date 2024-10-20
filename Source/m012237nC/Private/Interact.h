#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};


class M012237NC_API IInteract
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AController* causer, bool canExit);
	
};
