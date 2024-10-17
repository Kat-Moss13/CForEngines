
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Scorable.generated.h"

UINTERFACE()
class UScorable : public UInterface
{
	GENERATED_BODY()
};


class M012237NC_API IScorable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void AddScore(int points);
};
