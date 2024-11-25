// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Button.h"
#include "Widget_WinScreen.h"

#include "Kismet/GameplayStatics.h"

UWidget_WinScreen::UWidget_WinScreen()
{
	StartAgainButton->OnClicked.AddDynamic(this, &UWidget_WinScreen::StartAgain);
}

void UWidget_WinScreen::StartAgain()
{
	UGameplayStatics::OpenLevel(this, "KFM_Map", true);
}
