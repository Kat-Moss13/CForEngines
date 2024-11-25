#pragma once

#include "CoreMinimal.h"
#include "Interact_Parent.h"
#include "Door_Interact.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractSuccessSignature, AController* ,player);
UCLASS()
class M012237NC_API ADoor_Interact : public AInteract_Parent
{
	GENERATED_BODY()

public:

	ADoor_Interact();
	UPROPERTY(BlueprintAssignable)
	FInteractSuccessSignature OnSuccess;

	virtual void Interact_Implementation(AController* cause, bool canExit) override;
};

