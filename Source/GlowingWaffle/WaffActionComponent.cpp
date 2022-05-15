// Fill out your copyright notice in the Description page of Project Settings.


#include "WaffActionComponent.h"

#include "WaffAction.h"


// Sets default values for this component's properties
UWaffActionComponent::UWaffActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWaffActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWaffActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + ":" + ActiveGameplayTag.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1,0.0f, FColor::White, DebugMsg);

	// ...
}

void UWaffActionComponent::AddAction(TSubclassOf<UWaffAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}
	UWaffAction* NewAction = NewObject<UWaffAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UWaffActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UWaffAction* Action : Actions)
	{
		if(!Action->CanStart(Instigator))
		{
			FString FailMsg = FString::Printf(TEXT("Fail to run: %s"), *ActionName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailMsg);
			continue;
		}
			
		if(Action && Action->ActonName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UWaffActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for(UWaffAction* Action : Actions)
	{
		if(!Action->IsRunning())
		{
			continue;
		}
		if(Action && Action->ActonName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}