// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Objective.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjective : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectiveIsCompleted, AActor*, ObjectiveCompleted);

/**
 * 
 */
class MYPROJECT4_API IObjective
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FString GetObjectiveTitle() const = 0;
	virtual FText GetObjectiveDescription() const = 0;
	virtual void ActivateObjective() = 0;
	virtual bool IsObjectiveCompleted() = 0;
	virtual void MarkAsCompleted() = 0;

	FObjectiveIsCompleted OnObjectiveCompleted;
};
