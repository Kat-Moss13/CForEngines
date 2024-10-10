﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"

class UHealthComponent;
class UTargetComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTargetDestroyedSignature, UTargetComponent*, target,
	AController*, destroyer, int, targetValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetRegisteredSignature, UTargetComponent*, target);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class M012237NC_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UTargetComponent();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnDestroyed;

	static inline FTargetRegisteredSignature onTargetRegistered;
	

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int _PointsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_GameRuleRequestTargets();
	
};
