#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreasureParent.generated.h"

class USphereComponent;
class UTreasureComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlapSignature, AController*, causer);

UCLASS()
class M012237NC_API ATreasureParent : public AActor
{
	GENERATED_BODY()

public:

	ATreasureParent();
	UPROPERTY(BlueprintAssignable)
	FOnOverlapSignature OnOverlap;

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTreasureComponent> _Treasure;

};
