#include "GameRule.h"


UGameRule::UGameRule()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UGameRule::Init()
{
	
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule::BroadcastPointsScores(AController* scorer, int points)
{
	OnPointsScored.Broadcast(scorer, points);
}



