// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaffGameplayInterface.h"
#include "WaffPickUp.h"
#include "GameFramework/Actor.h"
#include "WaffHealthPotion.generated.h"

/*
* React to Interact() // SGameplayInterface.h
* Inactivate for 10 seconds upon triggered (Invisible and unable to interact with)
* Re-activates on time elapsed to show mesh, and ready to be triggered again.
* Ignores interacting pawn if already at maximum health.
 */

UCLASS()
class GLOWINGWAFFLE_API AWaffHealthPotion : public AWaffPickUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWaffHealthPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Heal")
	float HealValue;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interact Implementation
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
