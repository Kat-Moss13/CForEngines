﻿#include "PC_FPS.h"


#include "ChangeWeapon.h"
#include "P_FPS.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GunSelectionMenu.h"
#include "Inputable.h"
#include "Widget_HUD.h"
#include "Widget_WinScreen.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"


FGenericTeamId APC_FPS::GetGenericTeamId() const
{
	FGenericTeamId _teamID = FGenericTeamId(2);
	return _teamID;
}

void APC_FPS::BeginPlay()
{
	Super::BeginPlay();
	if (_HUDWidgetClass)
	{
		_HUDWidget = CreateWidget<UWidget_HUD, APC_FPS*>(this, _HUDWidgetClass.Get());
	}
	if (_WinWidgetClass)
	{
		_WinWidget = CreateWidget<UWidget_WinScreen, APC_FPS*>(this, _WinWidgetClass.Get());
		
	}
	bEnableClickEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void APC_FPS::ChooseWeapon_Implementation()
{
	SetPause(true);
	SetShowMouseCursor(true);
	if (_GunWidgetClass)
	{
		_GunWidget = CreateWidget<UGunSelectionMenu, APC_FPS*>(this, _GunWidgetClass.Get());
		_GunWidget->AddToViewport();
		_GunWidget->OnStart.AddUniqueDynamic(this, &APC_FPS::GameStart);
		_GunWidget->OnChangedWeapon.AddUniqueDynamic(this, &APC_FPS::ChangeWeapon);
	}
}

void APC_FPS::FinishGame_Implementation()
{
	_HUDWidget->RemoveFromParent();
	if (_WinWidget)
	{
		_WinWidget->AddToViewport();
		SetPause(true);
		SetShowMouseCursor(true);
	}
}

void APC_FPS::GameStart()
{
	SetPause(false);
	SetShowMouseCursor(false);
	_GunWidget->RemoveFromParent();
	_HUDWidget->AddToViewport();
	_HUDWidget->UpdateHeatlh(1);
	ReloadPressed();
}

void APC_FPS::ChangeWeapon(UWeaponType* Weapon)
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UChangeWeapon::StaticClass()))
		{
			IChangeWeapon::Execute_UpdateWeapon(currentPawn, Weapon);
		}
	}
}

void APC_FPS::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APC_FPS::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APC_FPS::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APC_FPS::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APC_FPS::JumpReleased);
		EIP->BindAction(_FireAction, ETriggerEvent::Started, this, &APC_FPS::FirePressed);
		EIP->BindAction(_FireAction, ETriggerEvent::Completed, this, &APC_FPS::FireReleased);
		EIP->BindAction(_InteractAction, ETriggerEvent::Triggered, this, &APC_FPS::InteractPressed);
		EIP->BindAction(_CrouchAction, ETriggerEvent::Started, this, &APC_FPS::CrouchPressed);
		EIP->BindAction(_CrouchAction, ETriggerEvent::Completed, this, &APC_FPS::CrouchReleased);
		EIP->BindAction(_SprintAction, ETriggerEvent::Started, this, &APC_FPS::SprintPressed);
		EIP->BindAction(_SprintAction, ETriggerEvent::Completed, this, &APC_FPS::SprintReleased);
		EIP->BindAction(_LeanLeftAction, ETriggerEvent::Started, this, &APC_FPS::LeanLeftPressed);
		EIP->BindAction(_LeanLeftAction, ETriggerEvent::Completed, this, &APC_FPS::LeanLeftReleased);
		EIP->BindAction(_LeanRightAction, ETriggerEvent::Started, this, &APC_FPS::LeanRightPressed);
		EIP->BindAction(_LeanRightAction, ETriggerEvent::Completed, this, &APC_FPS::LeanRightReleased);
		EIP->BindAction(_Reload, ETriggerEvent::Started, this, &APC_FPS::ReloadPressed);
	}
}

void APC_FPS::AddScore_Implementation(int points)
{
	_PlayerPoints += points;
	_HUDWidget->UpdateScore(_PlayerPoints);
}

void APC_FPS::ExitTrue_Implementation()
{
	_CanExit = true;
}

void APC_FPS::UpdateAmmoUI_Implementation(int CurrentAmmo, int MaxAmmo)
{
	_HUDWidget->UpdateAmmo(CurrentAmmo, MaxAmmo);
}

void APC_FPS::Look(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2D>();

	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Look(currentPawn, LookVector);
		}
	}
}

void APC_FPS::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void APC_FPS::JumpPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPressed(currentPawn);
		}
	}
}

void APC_FPS::JumpReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpReleased(currentPawn);
		}
	}
}

void APC_FPS::FirePressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FirePressed(currentPawn);
		}
	}
}

void APC_FPS::FireReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FireReleased(currentPawn);
		}
	}
}

void APC_FPS::InteractPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_InteractPressed(currentPawn, _CanExit);
		}
	}
}

void APC_FPS::CrouchPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchPressed(currentPawn);
		}
	}
}

void APC_FPS::CrouchReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchReleased(currentPawn);
		}
	}
}

void APC_FPS::SprintPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintPressed(currentPawn);
		}
	}
}

void APC_FPS::SprintReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintReleased(currentPawn);
		}
	}
}

void APC_FPS::LeanLeftPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_LeanLeftPressed(currentPawn);
		}
	}
}

void APC_FPS::LeanRightPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_LeanRightPressed(currentPawn);
		}
	}
}

void APC_FPS::LeanLeftReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_LeanLeftReleased(currentPawn);
		}
	}
}

void APC_FPS::LeanRightReleased()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_LeanRightReleased(currentPawn);
		}
	}
}

void APC_FPS::ReloadPressed()
{
	if (APawn* currentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_ReloadPressed(currentPawn);
		}
	}
}


void APC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);
			_PlayerPawn = IInputable::Execute_GetPawn(InPawn);
			_PlayerPawn->OnPawnDamaged.AddUniqueDynamic(this, &APC_FPS::UpdateHealth);
			ReloadPressed();
		}
	}
}

void APC_FPS::UpdateHealth(float newHealth, float maxHealth, float change)
{
	_HUDWidget->UpdateHeatlh(newHealth / 100.f);
}
