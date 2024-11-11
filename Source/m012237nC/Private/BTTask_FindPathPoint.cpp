﻿
#include "BTTask_FindPathPoint.h"

#include "AIPatrolPath.h"
#include "Inputable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint()
{
	NodeName = TEXT("FindPathPoint");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(_Key_Pawn.SelectedKeyName);

	auto const index = BBComp->GetValueAsInt(GetSelectedBlackboardKey());

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		FVector const Point = IInputable::Execute_GetPatrolPath(pawn)->GetPatrolPoints(index);

		UE::Math::TVector<double> const GlobalPoint = IInputable::Execute_GetPatrolPath(pawn)->GetActorTransform().
			TransformPosition(Point);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(_PathPointKey.SelectedKeyName, GlobalPoint);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;;
}
