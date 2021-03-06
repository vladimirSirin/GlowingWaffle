// Fill out your copyright notice in the Description page of Project Settings.


#include "WaffAttributeComponent.h"

#include "GlowingWaffleGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

// Console variables
static TAutoConsoleVariable<float> CVarDamageMultiplier(
	TEXT("su.DamageMultiplier"), 1.0f, TEXT("Globale Damage Multiplier for attribute components"),
	ECVF_Cheat);


// Sets default values for this component's properties
UWaffAttributeComponent::UWaffAttributeComponent()
{
	// Initialize the values
	HealthMax = 100;
	Health = HealthMax;

	bEnableRage = false;
	Rage = 0.0f;
	RageMax = 100.0f;

	// Replication
	SetIsReplicatedByDefault(true);
}

bool UWaffAttributeComponent::ApplyHealthChange(float Delta, AActor* Instigator)
{
	// is alive
	if (!IsAlive())
	{
		return false;
	}

	// CVar, damage multiplier applied
	if (Delta < 0.0f)
	{
		Delta *= CVarDamageMultiplier.GetValueOnGameThread();
	}


	// Check if in god
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	// Change the health num with delta
	const float OldHealth = Health;

	// Set a local new health for checking damage apply possible or not
	float NewHealthLocal = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	const float ActualDelta = NewHealthLocal - OldHealth;

	// Only apply and replicate when on server
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealthLocal;
		// Broadcast for health change delegate
		if (ActualDelta != 0.0)
		{
			MulticastOnHealthChanged(Instigator, Health, ActualDelta);
		}

		// Call On Actor Killed in Game mode if health is 0.0
		if (Health == 0.0f)
		{
			AGlowingWaffleGameModeBase* GM = GetWorld()->GetAuthGameMode<AGlowingWaffleGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), Instigator);
			}
		}

		// Apply rage change if damaged and enable rage
		if (bEnableRage && ActualDelta < 0)
		{
			ApplyRageChange(abs(ActualDelta) * RageTransRate->GetFloatValue(abs(ActualDelta)), Instigator);
		}
	}
	


	return ActualDelta != 0;
}

bool UWaffAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(-GetMaxHealth(), InstigatorActor);
}

bool UWaffAttributeComponent::ApplyRageChange(float Delta, AActor* Instigator)
{
	float OldRage = Rage;
	Rage = FMath::Clamp(Rage + Delta, 0.0f, RageMax);
	Rage = FMath::RoundToFloat(Rage);
	float ActualDelta = Rage - OldRage;

	// Broadcast for rage change delegate
	// OnRageChanged.Broadcast(Instigator, this, Rage, ActualDelta);
	MulticastOnRageChanged(Instigator, Rage, ActualDelta);
	UE_LOG(LogTemp, Log, TEXT("Changing Rage to %f"), Rage);

	return ActualDelta != 0;
}

bool UWaffAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float UWaffAttributeComponent::GetHealth() const
{
	return Health;
}

float UWaffAttributeComponent::GetHealthPercent() const
{
	return Health / HealthMax;
}

float UWaffAttributeComponent::GetMaxHealth() const
{
	return HealthMax;
}

bool UWaffAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float UWaffAttributeComponent::GetRagePercent() const
{
	return Rage / RageMax;
}

float UWaffAttributeComponent::GetRage() const
{
	return Rage;
}

void UWaffAttributeComponent::MulticastOnRageChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{
	OnRageChanged.Broadcast(InstigatorActor, this, NewRage, Delta);
}

void UWaffAttributeComponent::MulticastOnHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth,
                                                                      float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

UWaffAttributeComponent* UWaffAttributeComponent::GetAttributes(AActor* FromActor)
{
	UWaffAttributeComponent* AttriComp = Cast<UWaffAttributeComponent>(
		FromActor->GetComponentByClass(UWaffAttributeComponent::StaticClass()));

	if (AttriComp)
	{
		return AttriComp;
	}
	return nullptr;
}

bool UWaffAttributeComponent::IsActorAlive(AActor* ActorToCheck)
{
	if (const UWaffAttributeComponent* AttributeComponent = UWaffAttributeComponent::GetAttributes(ActorToCheck))
	{
		return AttributeComponent->IsAlive();
	}
	return false;
}

// prop replication
void UWaffAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWaffAttributeComponent, Health);
	DOREPLIFETIME(UWaffAttributeComponent, HealthMax);
	DOREPLIFETIME(UWaffAttributeComponent, Rage);
	DOREPLIFETIME(UWaffAttributeComponent, RageMax);

	// Used for optimization, only replicate when necessary
	// DOREPLIFETIME_CONDITION(UWaffAttributeComponent, HealthMax, COND_InitialOnly);
}
