// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"

#include "Combat.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(_Key_Pawn.SelectedKeyName);
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UCombat::StaticClass()))
	{
		AIPawn = ICombat::Execute_GetAIPawn(pawn);
	}

	APawn const*  player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), AIPawn->GetDistanceTo(player) <=MeleeRange);
}
