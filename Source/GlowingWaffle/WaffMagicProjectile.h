// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WaffAction.h"
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

	// Parry Tag
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	FGameplayTag ParryTag;

	// Status Effect on Damage tag
	UPROPERTY(EditDefaultsOnly, Category="Effect")
	TSubclassOf<UWaffAction> EffectActionClass;

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                      const FHitResult& SweepResult) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
