#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "Components/ActorComponent.h"
#include "TreasureComponent.generated.h"

class USphereComponent;
class UTreasureComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTreasurePickedUpSignature, UTreasureComponent*, treasure, AController*, causer, int, treasureValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTreasureRegisteredSignature, UTreasureComponent*, treasure);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class M012237NC_API UTreasureComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTreasureComponent();
	UPROPERTY(BlueprintAssignable)
	FTreasurePickedUpSignature onPickedUp;

	static inline FTreasureRegisteredSignature onTreasureRegistered;
	

	
protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int _TreasureValue;
	UPROPERTY(editanywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;
	
private:
	UFUNCTION()
	void Handle_PickedUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Handle_GameRuleRequestTreasure();
	UFUNCTION()
	void Handle_TreasureDestroyed(UTreasureComponent* target, AController* causer, int treasureValue);
};
