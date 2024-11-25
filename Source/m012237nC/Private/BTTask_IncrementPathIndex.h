#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrementPathIndex.generated.h"

UCLASS()
class M012237NC_API UBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_IncrementPathIndex();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_Pawn;

private:
	enum class EDirectionType { Forward, Reverse };

	EDirectionType Direction = EDirectionType::Forward; ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	bool bBiDirectional = false;
};
