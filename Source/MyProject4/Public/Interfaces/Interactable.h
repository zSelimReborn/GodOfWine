// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionSuccess, AActor*, InteractableObject, AActor*, InstigatorObject);

/**
 * 
 */
class MYPROJECT4_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// TODO EnableInteraction | DisableInteraction
	virtual void EnableInteraction() = 0;
	virtual void DisableInteraction() = 0;
	virtual bool CanInteract() const = 0;
	virtual void ShowInteractWidget() = 0;
	virtual void HideInteractWidget() = 0;
	virtual void StartInteraction(AActor* InteractionInstigator) = 0;
	virtual void EndInteraction(AActor* InteractionInstigator) = 0;

	FOnInteractionSuccess OnInteractionSuccess;
};
