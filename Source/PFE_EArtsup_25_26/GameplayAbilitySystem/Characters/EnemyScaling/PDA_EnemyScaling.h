// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_EnemyScaling.generated.h"

/**
 * 
 */
UCLASS()
class PFE_EARTSUP_25_26_API UPDA_EnemyScaling : public UPrimaryDataAsset
{
	GENERATED_BODY()
		
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling")
	float HealthScalingValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling") 
	float DamageScalingValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling")
	float SpeedScalingValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling")
	float ArmorScalingValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling")	
	int NumberOfLevelsToScaleArmor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Scaling")
	float TimeIntervalForScaling;
};
