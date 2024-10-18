#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Targets.generated.h"

class UTargetComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetRequestTargetsSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class M012237NC_API UGameRule_Targets : public UGameRule
{
	GENERATED_BODY()

public:

	UGameRule_Targets();

	static inline FGRTargetRequestTargetsSignature OnRequestTargets;

	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int _AmountRemaining;

private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue);
	
};
