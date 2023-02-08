// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interfaces/Objective.h"
#include "Lattice.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class MYPROJECT4_API ALattice : public AInteractableBase, public IObjective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALattice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Interaction(AActor* InteractionInstigator);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	virtual bool IsObjectiveCompleted() override;
	virtual void MarkAsCompleted() override;

// Specific tune
protected:
	UPROPERTY(EditAnywhere, Category="Grapes")
	int32 MaxGrapes = 20;

	UPROPERTY(EditAnywhere, Category="Grapes")
	int32 GrapesToComplete = 5;

	UPROPERTY(EditAnywhere, Category="Objective")
	FString ObjectiveTitle;

	UPROPERTY(EditAnywhere, Category="Objective")
	FText ObjectiveDescription;

	UPROPERTY(Transient)
	bool bIsObjectiveCompleted = false;

	UPROPERTY(Transient)
	int32 CurrentGrapes = MaxGrapes;
};
