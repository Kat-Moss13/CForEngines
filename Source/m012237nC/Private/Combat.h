#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combat.generated.h"

class AP_FPS;

UINTERFACE()
class UCombat : public UInterface
{
	GENERATED_BODY()
};


class M012237NC_API ICombat
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	APawn* GetAIPawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AP_FPS* GetSpecificPawn();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int MeleeAttack();
};
