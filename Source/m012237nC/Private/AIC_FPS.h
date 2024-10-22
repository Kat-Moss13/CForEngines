#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIC_FPS.generated.h"

UCLASS()
class M012237NC_API AAIC_FPS : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_FPS();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

};
