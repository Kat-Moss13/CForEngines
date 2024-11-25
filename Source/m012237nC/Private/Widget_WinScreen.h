#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_WinScreen.generated.h"
class UTextBlock;
class UButton;

UCLASS(Abstract, BlueprintType)
class M012237NC_API UWidget_WinScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WinText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartAgainButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StartAgainText;

	UFUNCTION()
	void StartAgain();
};
