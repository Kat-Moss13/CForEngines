// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "Inputable.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "FindRandomLocation";
	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, Key_Pawn), APawn::StaticClass());
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		FVector AIPosition = IInputable::Execute_PawnPosition(pawn);

		if(UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FNavLocation Location;
			if(NavSys->GetRandomPointInNavigableRadius(AIPosition, SearchRadius, Location))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
			}
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
