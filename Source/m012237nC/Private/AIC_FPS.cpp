﻿#include "AIC_FPS.h"

#include "Inputable.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AAIC_FPS::AAIC_FPS()
{
	PrimaryActorTick.bCanEverTick = true;
	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	_AISense_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));
	_AISense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectNeutrals = true;

	_AIPerception->ConfigureSense(*_AISense_Sight);
	_AIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AAIC_FPS::BeginPlay()
{
	Super::BeginPlay();
	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIC_FPS::Handle_TargetPerceptionUpdated);
	
}

void AAIC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
	{

		RunBehaviorTree(IInputable::Execute_GetBehaviorTree(InPawn));
	}
}

ETeamAttitude::Type AAIC_FPS::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId TeamIDNumber(FGenericTeamId::GetTeamIdentifier(&Other));
	if(TeamIDNumber == FGenericTeamId(1))
	{
		return ETeamAttitude::Friendly;
	}
	if(TeamIDNumber == FGenericTeamId(2))
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Neutral;
}

void AAIC_FPS::Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
	case 0:
		GetBlackboardComponent()->SetValueAsVector(FName("TargetPosition"), Actor->GetActorLocation());
		//GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
		
	
	default:
		return;
	}
}



