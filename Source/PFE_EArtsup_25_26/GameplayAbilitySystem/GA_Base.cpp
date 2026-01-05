// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Base.h"

FText UGA_Base::GetBasicName() const
{
	if (!AbilityDisplayName.IsEmpty())
		return AbilityDisplayName;

	// fallback : nettoyer le nom de la classe (ex: "GA_Dash_C" -> "Dash")
	FString ClassName = GetClass()->GetName();
	ClassName.RemoveFromEnd(TEXT("_C"));
	// optionel : retirer préfixes comme "GA_"
	if (ClassName.StartsWith(TEXT("GA_")))
	{
		ClassName = ClassName.RightChop(3);
	}
	return FText::FromString(ClassName);
}

UGA_Base::UGA_Base()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
}

bool UGA_Base::HasPc() const
{
	const APawn* PawnObject = Cast<APawn>(GetOwningActorFromActorInfo());
	if (!PawnObject)
	{
		return false;
	}
	return PawnObject->GetController()->IsA<APlayerController>();
}