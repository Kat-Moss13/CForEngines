#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MeleeAttack.generated.h"


class AP_FPS;

UCLASS()
class M012237NC_API UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MeleeAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector _Key_Pawn;

	AP_FPS* AIPawn;

private:
	bool MontageHasFinished(AP_FPS* const AINpc);
};
