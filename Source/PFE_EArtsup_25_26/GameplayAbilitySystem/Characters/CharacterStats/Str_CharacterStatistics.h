// cpp
#pragma once

#include "CoreMinimal.h"
#include "Str_CharacterStatistics.generated.h"

USTRUCT(BlueprintType)
struct FStr_CharacterStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	int MaxHealthValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float RunSpeedValue = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float LifeStealValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float ArmorValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float AttackSpeedValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float AttackValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float DashDistanceValue = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float DashTimeValue = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Stats")
	float DashCooldownValue = 1.f;
};
