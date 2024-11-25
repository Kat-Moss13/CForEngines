#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsPlayerInMeleeRange.generated.h"


UCLASS()
class M012237NC_API UBTService_IsPlayerInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IsPlayerInMeleeRange();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector _Key_Pawn;

	APawn* AIPawn;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", Meta = (AllowPrivateAccess = "true"))
	float MeleeRange = 2.5f;
};
