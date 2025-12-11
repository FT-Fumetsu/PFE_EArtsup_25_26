// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttributeSet.h"
#include "GameplayEffectExtension.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Experience = 0.f;
	MaxExperience = 100.f;
	Levels = 0.f;
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	} else if (Attribute == GetExperienceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxExperience());
	}
	else if (Attribute == GetLevelsAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	} else if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
	{
		SetExperience(GetExperience());
	} else if (Data.EvaluatedData.Attribute == GetLevelsAttribute())
	{
		SetLevels(GetLevels());
	}
}