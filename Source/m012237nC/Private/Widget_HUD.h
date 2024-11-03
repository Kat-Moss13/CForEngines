﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS(Abstract, BlueprintType)
class M012237NC_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateHeatlh(float newHealthRatio);
	void UpdateScore(int newScore);
	void UpdateAmmo(int newCurrent, int newMax);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentAmmoText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxAmmoText;
};
