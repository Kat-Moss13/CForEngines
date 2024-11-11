// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"

#include "Inputable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("ChangeSpeed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(_Key_Pawn.SelectedKeyName);

	auto const index = BBComp->GetValueAsInt(GetSelectedBlackboardKey());

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_SetMaxWalkSpeed(pawn, _Speed);
	}
}
