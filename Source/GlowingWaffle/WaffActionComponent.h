// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "WaffActionComponent.generated.h"

class UWaffAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLOWINGWAFFLE_API UWaffActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Tags")
	FGameplayTagContainer ActiveGameplayTag;
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<UWaffAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TArray<TSubclassOf<UWaffAction>> DefaultActions;
	
	// Sets default values for this component's properties
	UWaffActionComponent();

protected:
	// Action list
	UPROPERTY(EditDefaultsOnly)
	TArray<UWaffAction*> Actions;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
