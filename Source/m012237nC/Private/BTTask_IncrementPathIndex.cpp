#include "BTTask_IncrementPathIndex.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "AIPatrolPath.h"
#include "Inputable.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex()
{
	NodeName = TEXT("IncrementPathIndex");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		int const NoOfPoints = IInputable::Execute_GetPatrolPath(pawn)->Num();
		int const MinIndex = 0;
		int const MaxIndex = NoOfPoints - 1;
		int32 Index = BBComp->GetValueAsInt(GetSelectedBlackboardKey());

		if(bBiDirectional)
		{
			if(Index >= MaxIndex && Direction == EDirectionType::Forward)
			{
				Direction = EDirectionType::Reverse;
			}
			else if(Index == MinIndex && Direction == EDirectionType::Reverse)
			{
				Direction = EDirectionType::Forward;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++Index: --Index) % NoOfPoints);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
