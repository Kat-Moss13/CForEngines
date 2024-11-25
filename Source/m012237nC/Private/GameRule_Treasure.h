#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Treasure.generated.h"
class UTreasureComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTreasureRequestTreasuresSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class M012237NC_API UGameRule_Treasure : public UGameRule
{
	GENERATED_BODY()

public:

	UGameRule_Treasure();

	static inline FGRTreasureRequestTreasuresSignature OnRequestTreasures;

	virtual void Init() override;
	
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTreasureComponent>> _Treasures;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _NeededTreasure;
	
	int _AmountRemaining;

private:
	UFUNCTION()
	void Handle_TreasureRegistered(UTreasureComponent* treasure);
	UFUNCTION()
	void Handle_TreasureRemoved(UTreasureComponent* treasure, AController* causer, int treasureValue );
	
	
};
