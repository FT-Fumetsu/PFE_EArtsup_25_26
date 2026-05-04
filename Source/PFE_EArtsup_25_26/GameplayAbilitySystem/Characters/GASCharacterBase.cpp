// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PFE_EArtsup_25_26/GameplayAbilitySystem/PfeAbilitySystemComponent.h"
#include "PFE_EArtsup_25_26/GameplayAbilitySystem/AttributeSets/BasicAttributeSet.h"

// Sets default values
AGASCharacterBase::AGASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UPfeAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(false);
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	// Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeeSet"));
	
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("State.Dead"))
		.AddUObject(this, &AGASCharacterBase::OnDeadTagChanged);
}

// Called when the game starts or when spawned
void AGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetRunSpeedAttribute()).AddUObject(this, &AGASCharacterBase::OnRunSpeedChanged);
	}
	
	MergeStats();
}

// Called every frame
void AGASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AGASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartingAbilities);
		
		InitializeAttributes();
	}
}

void AGASCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();	
	}
}

void AGASCharacterBase::InitializeAttributes()
{
	if (bAttributesInitialized) return;
	if (!AbilitySystemComponent) return;
	if (!DefaultStats) return;

	// Si une classe d'AttributeSet est fournie, instancier et l'ajouter à l'ASC
	if (BasicAttributeSetClass && !BasicAttributeSetInstance)	
	{
		BasicAttributeSetInstance = NewObject<UBasicAttributeSet>(this, BasicAttributeSetClass);
		if (BasicAttributeSetInstance)
		{
			AbilitySystemComponent->AddAttributeSetSubobject(BasicAttributeSetInstance);
		}
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultStats, 1.0f, EffectContext);
	if (SpecHandle.IsValid() && SpecHandle.Data.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		bAttributesInitialized = true;
	}
}

void AGASCharacterBase::MergeStats()
{
	if (StatsData)
	{
		FinalStats = StatsData->CharacterStats;
	}

	if (StatsOverride.MaxHealthValue > 0.f)
	{
		FinalStats.MaxHealthValue = StatsOverride.MaxHealthValue;
	}

	if (StatsOverride.RunSpeedValue > 0.f)
	{
		FinalStats.RunSpeedValue = StatsOverride.RunSpeedValue;
	}
	
	FinalStats.LifeStealValue = StatsOverride.LifeStealValue;
	
	FinalStats.ArmorValue = StatsOverride.ArmorValue;
	
	FinalStats.AttackSpeedValue = StatsOverride.AttackSpeedValue;
	
	FinalStats.AttackValue = StatsOverride.AttackValue;
	
	if (StatsOverride.DashDistanceValue > 0.f)
	{
		FinalStats.DashDistanceValue = StatsOverride.DashDistanceValue;
	}
	
	if (StatsOverride.DashTimeValue > 0.f)
	{
		FinalStats.DashTimeValue = StatsOverride.DashTimeValue;
	}
	
	if (StatsOverride.DashCooldownValue > 0.f)
	{
		FinalStats.DashCooldownValue = StatsOverride.DashCooldownValue;
	}
}

TArray<FGameplayAbilitySpecHandle> AGASCharacterBase::GrantAbilities(
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent)
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}
	
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	
	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
			Ability, 1, -1, this
			));
		AbilityHandles.Add(SpecHandle);
	}
	
	SendAbilitiesChangedEvent();
	return AbilityHandles;
}

void AGASCharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	
	for (FGameplayAbilitySpecHandle AbilityHandle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}
	
	SendAbilitiesChangedEvent();
}

void AGASCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

void AGASCharacterBase::HandleDeath_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	
	FVector Impulse = GetActorForwardVector() * -20000;
	Impulse.Z = 15000;
	GetMesh()->AddImpulseAtLocation(Impulse, GetActorLocation());
}

void AGASCharacterBase::OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		HandleDeath();
	}
}

void AGASCharacterBase::LoadAttributes(TMap<FGameplayAttribute, float> SavedAttributesMap) const
{
	for (const TPair<FGameplayAttribute, float>& Pair : SavedAttributesMap)
	{
		FGameplayAttribute Attribute = Pair.Key;
		float Value = Pair.Value;
		AbilitySystemComponent->ApplyModToAttribute(Attribute, EGameplayModOp::Override, Value);
	}
}

void AGASCharacterBase::OnRunSpeedChanged(const FOnAttributeChangeData& Data) const
{
	float NewRunSpeed = Data.NewValue;
	GetCharacterMovement()->MaxWalkSpeed = NewRunSpeed;
}
