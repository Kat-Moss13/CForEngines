// Fill out your copyright notice in the Description page of Project Settings.


#include "BBTask_FindPlayerLocation.h"

#include "Inputable.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBBTask_FindPlayerLocation::UBBTask_FindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBBTask_FindPlayerLocation, Key_Pawn), APawn::StaticClass());
}

EBTNodeResult::Type UBBTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		FVector Position = IInputable::Execute_PawnPosition(pawn);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Position);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
		
	}
	

	return EBTNodeResult::Failed;
}
