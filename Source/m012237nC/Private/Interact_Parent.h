#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "GameFramework/Actor.h"
#include "Interact_Parent.generated.h"

class UBoxComponent;
UCLASS()
class M012237NC_API AInteract_Parent : public AActor, public IInteract
{
	GENERATED_BODY()

public:

	AInteract_Parent();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

private:
	
	
};
