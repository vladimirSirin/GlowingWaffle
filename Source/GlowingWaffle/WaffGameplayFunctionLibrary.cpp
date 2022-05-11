// Fill out your copyright notice in the Description page of Project Settings.


#include "WaffGameplayFunctionLibrary.h"

#include "WaffAttributeComponent.h"

bool UWaffGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if (UWaffAttributeComponent* AttributeComponent = UWaffAttributeComponent::GetAttributes(TargetActor))
	{
		return AttributeComponent->ApplyHealthChange(-DamageAmount, DamageCauser);
	}
	return false;
}

bool UWaffGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
                                                          const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
			
		}
		return true;
	}
	return false;
}
