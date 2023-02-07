// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Lyre.generated.h"

class UWidgetComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class MYPROJECT4_API ALyre : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALyre();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interaction(AActor*);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Interactable interface
public:
	virtual void EnableInteraction() override;
	virtual void DisableInteraction() override;
	virtual bool CanInteract() const override;
	virtual void StartInteraction(AActor* InteractionInstigator) override;
	virtual void EndInteraction(AActor* InteractionInstigator) override;

	FORCEINLINE bool HasBeenPlayed() const { return bHasBeenPlayed; }

// Specific tune
protected:
	UPROPERTY(EditAnywhere, Category="Music")
	TObjectPtr<USoundCue> LyreMusic;

	UPROPERTY(EditAnywhere, Category="Music")
	float MinPitchMultiplier = 0.8f;

	UPROPERTY(EditAnywhere, Category="Music")
	float MaxPitchMultiplier = 1.2f;

	UPROPERTY(Transient)
	bool bHasBeenPlayed = false;
};
