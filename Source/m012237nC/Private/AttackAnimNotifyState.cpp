#include "AttackAnimNotifyState.h"

#include "Combat.h"
#include "Kismet/KismetSystemLibrary.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(MeshComp->GetOwner(), UCombat::StaticClass()))
		{
			ICombat::Execute_AttackStart(MeshComp->GetOwner());
		}
	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(MeshComp->GetOwner(), UCombat::StaticClass()))
		{
			ICombat::Execute_AttackEnd(MeshComp->GetOwner());
		}
	}
}
