﻿#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIC_FPS.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;


UCLASS()
class M012237NC_API AAIC_FPS : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_FPS();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlackboardComponent> _Blackboard;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;
	TObjectPtr<UAISenseConfig_Sight> _AISense_Sight;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

};
