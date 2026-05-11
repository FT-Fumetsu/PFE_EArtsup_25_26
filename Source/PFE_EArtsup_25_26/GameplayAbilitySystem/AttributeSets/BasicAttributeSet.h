// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PFE_EARTSUP_25_26_API UBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UBasicAttributeSet(); // Constructor
	
	// Health Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Health); // Macro to generate getter and setter
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxHealth);
	
	// Experience Attributes
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Experience")
    FGameplayAttributeData Experience;
    ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Experience);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Experience")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxExperience);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Experience")
	FGameplayAttributeData Levels;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Levels);
	
	// Stats attributes
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, RunSpeed);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/LifeSteal")
	FGameplayAttributeData LifeSteal;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, LifeSteal);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/LifeSteal")
	FGameplayAttributeData MaxLifeSteal;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxLifeSteal);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Armor")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Armor")
	FGameplayAttributeData MinArmor;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MinArmor);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Armor")
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MaxArmor);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Armor")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, AttackSpeed);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Armor")
	FGameplayAttributeData GlobalAttackDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, GlobalAttackDamage);
	
	// Dash Attributes
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData DashDistance;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, DashDistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData DashTime;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, DashTime);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData MinDashTime;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MinDashTime);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData DashCooldown;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, DashCooldown);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData MinDashCooldown;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, MinDashCooldown);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData DashDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, DashDamage);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes/Dash")
	FGameplayAttributeData DashKnockback;
	ATTRIBUTE_ACCESSORS_BASIC(UBasicAttributeSet, DashKnockback);
	
public:
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
};
