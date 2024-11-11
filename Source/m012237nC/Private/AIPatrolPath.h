#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPath.generated.h"

UCLASS()
class M012237NC_API AAIPatrolPath : public AActor
{
	GENERATED_BODY()

public:

	AAIPatrolPath();

	FVector GetPatrolPoints(int const index) const;
	int Num() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(MakeEditWidget="true", AllowPrivateAccess="true"))
	TArray<FVector> PatrolPoints;
};
