#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, scorer, int, points);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class M012237NC_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:

	UGameRule();

	FGameRuleCompleteSignature OnComplete;
	FGameRulePointsScoredSignature OnPointsScored;

	UFUNCTION()
	virtual void Init();

protected:
	void BroadcastComplete();
	void BroadcastPointsScores(AController* scorer, int points);
};
