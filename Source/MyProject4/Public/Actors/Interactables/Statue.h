// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/InteractableBase.h"
#include "Interfaces/Objective.h"
#include "Statue.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API AStatue : public AInteractableBase, public IObjective
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void Interaction(AActor* InteractionInstigator);

// Interactable interface
public:
	virtual bool CanInteract() const override;
	virtual void StartInteraction(AActor* InteractionInstigator) override;
	virtual void EndInteraction(AActor* InteractionInstigator) override;

// Objective interface
public:
	virtual FString GetObjectiveTitle() const override;
	virtual FText GetObjectiveDescription() const override;
	virtual void ActivateObjective() override;
	virtual void DeactivateObjective() override;
	virtual bool IsObjectiveCompleted() override;
	virtual void MarkAsCompleted() override;

protected:
	UPROPERTY(EditAnywhere, Category="Objective")
	FString ObjectiveTitle;

	UPROPERTY(EditAnywhere, Category="Objective")
	FText ObjectiveDescription;

	UPROPERTY(Transient)
	bool bIsObjectiveCompleted = false;
};
