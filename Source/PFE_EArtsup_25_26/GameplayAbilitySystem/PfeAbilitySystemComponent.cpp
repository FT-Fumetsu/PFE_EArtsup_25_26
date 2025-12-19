// Fill out your copyright notice in the Description page of Project Settings.


#include "PfeAbilitySystemComponent.h"


// Sets default values for this component's properties
UPfeAbilitySystemComponent::UPfeAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPfeAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPfeAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPfeAbilitySystemComponent::BP_AbilityLocalInputPressed(int32 InputID)
{
	AbilityLocalInputPressed(InputID);
}

void UPfeAbilitySystemComponent::BP_AbilityLocalInputReleased(int32 InputID)
{
	AbilityLocalInputReleased(InputID);
}

