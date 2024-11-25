#include "GameRule.h"


UGameRule::UGameRule()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGameRule::Init()
{
}

void UGameRule::BroadcastComplete(AController* scorer)
{
	OnComplete.Broadcast(scorer);
}

void UGameRule::BroadcastPointsScores(AController* scorer, int points)
{
	OnPointsScored.Broadcast(scorer, points);
}
