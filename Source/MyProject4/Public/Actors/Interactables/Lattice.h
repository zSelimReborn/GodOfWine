// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Lattice.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class MYPROJECT4_API ALattice : public AInteractableBase
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

// Specific tune
protected:
	UPROPERTY(EditAnywhere, Category="Grapes")
	int32 MaxGrapes = 20;

	UPROPERTY(Transient)
	int32 CurrentGrapes = MaxGrapes;
};
