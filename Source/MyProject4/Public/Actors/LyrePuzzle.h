// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LyrePuzzle.generated.h"

class AInteractableBase;
class USoundCue;

UCLASS()
class MYPROJECT4_API ALyrePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALyrePuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ScheduleSuccessSound();
	void ScheduleFailSound();
	void PlaySound(USoundCue* Sound) const;
	void PlaySuccessSound();
	void PlayFailSound();

	void DisableAllInteractables();
	void EnableAllInteractables();
	void PrepareInteractables();
	void HandleSuccess();
	void HandleFail();

	UFUNCTION()
	void Interaction(AActor* InteractableActor, AActor* ActorInstigator);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Blueprint interface
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteraction(AInteractableBase* Interactable);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSuccessPuzzle();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFailPuzzle();
	
protected:
	UPROPERTY(EditAnywhere, Category="Puzzle")
	TArray<AInteractableBase*> Interactables;

	UPROPERTY(EditAnywhere, Category="Puzzle")
	TObjectPtr<USoundCue> SuccessSound;

	UPROPERTY(EditAnywhere, Category="Puzzle")
	TObjectPtr<USoundCue> FailSound;

	UPROPERTY(EditAnywhere, Category="Puzzle")
	float PlaySoundAfterSeconds = 1.f;

	FTimerHandle PuzzleFeedbackTimerHandle;

	UPROPERTY(Transient)
	int8 CurrentPuzzleIndex = 0;

	UPROPERTY(Transient)
	int8 SuccessInteractions = 0;
};
