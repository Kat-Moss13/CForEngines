#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeSpeed.generated.h"


UCLASS()
class M012237NC_API UBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector _Key_Pawn;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AI", meta = (AllowPrivateAccess = "true"))
	float _Speed = 500.f;
};
