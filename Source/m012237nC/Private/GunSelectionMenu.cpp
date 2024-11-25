#include "GunSelectionMenu.h"
#include "WeaponType.h"
#include "Components/Button.h"
#include "String/ParseTokens.h"

void UGunSelectionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UGunSelectionMenu::StartGame);
	BarettaButton->OnClicked.AddDynamic(this, &UGunSelectionMenu::SetBaretta);
	GlockButton->OnClicked.AddDynamic(this, &UGunSelectionMenu::SetGlock);
	M16Button->OnClicked.AddDynamic(this, &UGunSelectionMenu::SetM16);
}


void UGunSelectionMenu::UpdateGunSelection(UWeaponType* weaponChosen)
{
	OnChangedWeapon.Broadcast(weaponChosen);
}

void UGunSelectionMenu::StartGame()
{
	if (WeaponSelected == false)
	{
		SetBaretta();
		UpdateGunSelection(_WeaponChosen);
	}
	UpdateGunSelection(_WeaponChosen);
	OnStart.Broadcast();
}

void UGunSelectionMenu::SetBaretta()
{
	for (int i = 0; i < _Weapons.Num(); i++)
	{
		if (_Weapons[i]->GetName().Contains("Baretta"))
		{
			_WeaponChosen = _Weapons[i];
			WeaponSelected = true;
		}
	}
}

void UGunSelectionMenu::SetGlock()
{
	for (int i = 0; i < _Weapons.Num(); i++)
	{
		if (_Weapons[i]->GetName().Contains("Glock"))
		{
			_WeaponChosen = _Weapons[i];
			WeaponSelected = true;
		}
	}
}

void UGunSelectionMenu::SetM16()
{
	for (int i = 0; i < _Weapons.Num(); i++)
	{
		if (_Weapons[i]->GetName().Contains("M16"))
		{
			_WeaponChosen = _Weapons[i];
			WeaponSelected = true;
		}
	}
}
