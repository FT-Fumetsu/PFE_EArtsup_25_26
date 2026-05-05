// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "EnemyScaling/PDA_EnemyScaling.h"
#include "CharacterStats/PDA_CharacterStatistics.h"
#include "CharacterStats/Str_CharacterStatistics.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "GASCharacterBase.generated.h"

UCLASS()
class PFE_EARTSUP_25_26_API AGASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacterBase();
	
	// Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TSubclassOf<class UBasicAttributeSet> BasicAttributeSetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UBasicAttributeSet* BasicAttributeSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool hasWeaponEquipped = false;
	
	// Base data
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UPDA_CharacterStatistics* StatsData;

	// Override (POOL / SPAWN)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true), Category = "Stats")
	FStr_CharacterStatistics StatsOverride;

	// Final runtime stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	FStr_CharacterStatistics FinalStats;

	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBasicAttributeSet* BasicAttributeSetInstance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AbilitySystem")
	TSubclassOf<UGameplayEffect> DefaultStats;
	
	bool bAttributesInitialized = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Scaling")
	UPDA_EnemyScaling* EnemyScalingData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	
	virtual void OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void HandleDeath();
	
	void InitializeAttributes();
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void SendAbilitiesChangedEvent();
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void LoadAttributes(TMap<FGameplayAttribute, float> SavedAttributesMap) const;
	
	void OnRunSpeedChanged(const FOnAttributeChangeData& Data) const;
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void MergeStats();
	
	// Pooling
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	void ResetForReuse();
	
};
