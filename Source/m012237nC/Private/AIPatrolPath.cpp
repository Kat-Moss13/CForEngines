
#include "AIPatrolPath.h"


AAIPatrolPath::AAIPatrolPath()
{

	PrimaryActorTick.bCanEverTick = false;
}

FVector AAIPatrolPath::GetPatrolPoints(int const index) const
{
	return PatrolPoints[index];
}

int AAIPatrolPath::Num() const
{

	return PatrolPoints.Num();
}



