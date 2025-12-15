// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "GA_Base.generated.h"

/**
 * 
 */
UCLASS()
class PFE_EARTSUP_25_26_API UGA_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public: 
	
	UGA_Base();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText AbilityDisplayName;

	// Description courte, localisable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta=(MultiLine=true))
	FText AbilityDescription;

	// Icône affichée dans l'UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* AbilityIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool CanBeShownInUi;
		
	// Utilitaire : fallback pour obtenir un nom lisible (peut être utilisé en C++)
	UFUNCTION(BlueprintCallable, Category="UI")
	FText GetBasicName() const;
};
