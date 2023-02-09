// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllObjectivesCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectiveActivated, AActor*, ObjectiveActivated, const FString&, ObjectiveTitle, const FText&, ObjectiveDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectiveCompleted, AActor*, ObjectiveCompleted, const FString&, ObjectiveTitle, const FText&, ObjectiveDescription);

class IObjective;

/**
 * 
 */
UCLASS()
class MYPROJECT4_API UObjectiveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ObjectiveCompleted(AActor* ObjectiveActor);
	void ActivateCurrentObjective();
	
public:
	UFUNCTION(BlueprintCallable)
	void AddObjective(AActor* ObjectiveActor);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveTitle() const;

	UFUNCTION(BlueprintCallable)
	FText GetCurrentObjectiveDescription() const;
	
	void FireObjectivesCompletedEvent();
	
	UFUNCTION(BlueprintCallable)
	void OnMapStart();

	bool IsAnObjectiveQueued(const AActor* ObjectiveActor) const;

// Variables
protected:
	FTimerHandle ObjectivesCompletedTimer;

	UPROPERTY(Transient)
	TArray<TScriptInterface<IObjective>> Objectives;

	UPROPERTY(Transient)
	int32 CurrentObjectiveIndex = 0;
	
// Events
public:
	UPROPERTY(BlueprintAssignable)
	FAllObjectivesCompleted OnAllObjectivesCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveActivated OnObjectiveActivated;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectiveCompleted OnObjectiveCompleted;
};
