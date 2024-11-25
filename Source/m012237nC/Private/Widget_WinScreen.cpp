// Fill out your copyright notice in the Description page of Project Settings.
#include "Widget_WinScreen.h"
#include "Components/Button.h"


#include "Kismet/GameplayStatics.h"


void UWidget_WinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	StartAgainButton->OnClicked.AddDynamic(this, &UWidget_WinScreen::StartAgain);
}

void UWidget_WinScreen::StartAgain()
{
	UGameplayStatics::OpenLevel(this, "KFM_Map", true);
}
