// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "Combat.h"
#include "P_FPS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(_Key_Pawn.SelectedKeyName);

	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UCombat::StaticClass()))
	{
		AIPawn = ICombat::Execute_GetSpecificPawn(pawn);
	}

	if (UKismetSystemLibrary::DoesImplementInterface(pawn, UCombat::StaticClass()))
	{
		if (MontageHasFinished(AIPawn))
		{
			ICombat::Execute_MeleeAttack(pawn);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::MontageHasFinished(AP_FPS* const AINpc)
{
	return AINpc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(AINpc->GetMontage());
}
