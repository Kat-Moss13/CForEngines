
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_WinScreen.generated.h"
class UTextBlock;
class UButton;

UCLASS()
class M012237NC_API UWidget_WinScreen : public UUserWidget
{
	GENERATED_BODY()
	UWidget_WinScreen();
	
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
