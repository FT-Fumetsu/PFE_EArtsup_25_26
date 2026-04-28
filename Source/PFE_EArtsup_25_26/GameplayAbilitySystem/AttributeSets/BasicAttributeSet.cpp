// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	Health = 100;
	MaxHealth = 100;
	Experience = 0.f;
	MaxExperience = 100.f;
	Levels = 0;
	RunSpeed = 500.f;
	LifeSteal = 0.f;
	MaxLifeSteal = 50.f;
	Armor = 0.f;
	MinArmor = -50.f;
	MaxArmor = 50.f;
	DashDistance = 600.f;
	DashTime = .5f;
	MinDashTime = 0.01f;
	DashCooldown = 3.f;
	MinDashCooldown = 0.5f;
	DashDamage = 0.f;
	DashKnockback = 0.f;
	AttackSpeed = 0.f;
	GlobalAttackDamage = 0.f;
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetExperienceAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetLevelsAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetRunSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetLifeStealAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxLifeSteal());
	}
	else if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, GetMinArmor(), GetMaxArmor());
	}
	else if (Attribute == GetDashDistanceAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetDashTimeAttribute())
	{
		NewValue = FMath::Max(NewValue, GetMinDashTime());
	}
	else if (Attribute == GetDashCooldownAttribute())
	{
		NewValue = FMath::Max(NewValue, GetMinDashCooldown());
	}
	else if (Attribute == GetDashDamageAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetDashKnockbackAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}
	else if (Attribute == GetAttackSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, -1.f);
	}
	else if (Attribute == GetGlobalAttackDamageAttribute())
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
			
		if (Data.EffectSpec.Def->GetAssetTags().HasTag(FGameplayTag::RequestGameplayTag("Effects.HitReaction")))
		{
			FGameplayTagContainer HitReactionTagContainer;
			HitReactionTagContainer.AddTag(FGameplayTag::RequestGameplayTag("GameplayAbility.HitReaction"));
			GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(HitReactionTagContainer);
		}
	} else if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
	{
		float CurrentXP = GetExperience();
		float MaxXP = GetMaxExperience();
		
		int32 CurrentLevel = GetLevels();
		
		while (CurrentXP >= MaxXP && MaxXP > 0.f)
		{
			CurrentXP -= MaxXP;
			CurrentLevel += 1;
			
			if (UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
			{
				FGameplayEventData Payload;
				Payload.EventTag = FGameplayTag::RequestGameplayTag("Event.LevelUp");
				//Payload.EventMagnitude = CurrentLevel;

				ASC->HandleGameplayEvent(Payload.EventTag, &Payload);
			}
			
			MaxXP = 100.f + 20 * CurrentLevel;
		}
		
		SetExperience(CurrentXP);
		SetMaxExperience(MaxXP);
		SetLevels(CurrentLevel);
		
	} else if (Data.EvaluatedData.Attribute == GetLevelsAttribute())
	{
		SetLevels(GetLevels());
	} else if (Data.EvaluatedData.Attribute == GetRunSpeedAttribute())
	{
		SetRunSpeed(GetRunSpeed());
	} else if (Data.EvaluatedData.Attribute == GetLifeStealAttribute())
	{
		SetLifeSteal(GetLifeSteal());
	} else if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(GetArmor());
	} else if (Data.EvaluatedData.Attribute == GetDashDistanceAttribute())
	{
		SetDashDistance(GetDashDistance());
	} else if (Data.EvaluatedData.Attribute == GetDashTimeAttribute())
	{
		SetDashTime(GetDashTime());
	} else if (Data.EvaluatedData.Attribute == GetDashCooldownAttribute())
	{
		SetDashCooldown(GetDashCooldown());
	} else if (Data.EvaluatedData.Attribute == GetDashDamageAttribute())
	{
		SetDashDamage(GetDashDamage());
	} else if (Data.EvaluatedData.Attribute == GetDashKnockbackAttribute())
	{
		SetDashKnockback(GetDashKnockback());
	} else if (Data.EvaluatedData.Attribute == GetAttackSpeedAttribute())
	{
		SetAttackSpeed(GetAttackSpeed());
	}
	else if (Data.EvaluatedData.Attribute == GetGlobalAttackDamageAttribute())
	{
		SetGlobalAttackDamage(GetGlobalAttackDamage());
	}
}

void UBasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, const float OldValue, const float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue); 
	
	if (Attribute == GetHealthAttribute() && NewValue <= 0.f)
	{
		FGameplayTagContainer DeathAbilityTagContainer;
		DeathAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag("GameplayAbility.Death"));
		GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(DeathAbilityTagContainer);
	}
}
