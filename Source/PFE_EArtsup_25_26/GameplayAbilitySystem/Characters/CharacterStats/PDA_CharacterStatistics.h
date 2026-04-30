// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Str_CharacterStatistics.h"
#include "Engine/DataAsset.h"
#include "PDA_CharacterStatistics.generated.h"

/**
 * 
 */
UCLASS()
class PFE_EARTSUP_25_26_API UPDA_CharacterStatistics : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	FStr_CharacterStatistics CharacterStats;
};
