// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaffProjectile.h"
#include "WaffMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class GLOWINGWAFFLE_API AWaffMagicProjectile : public AWaffProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaffMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//// Setup the Necessary Components.
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//USphereComponent* SphereComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UProjectileMovementComponent* MoveComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UParticleSystemComponent* ParticleComp;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
