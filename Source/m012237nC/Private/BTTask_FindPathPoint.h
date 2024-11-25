#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPathPoint.generated.h"


UCLASS()
class M012237NC_API UBTTask_FindPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindPathPoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector _Key_Pawn;

private:
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector _PathPointKey;
};
