// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LyrePuzzle.h"

#include "Sound/SoundCue.h"
#include "Actors/Interactables/InteractableBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALyrePuzzle::ALyrePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALyrePuzzle::BeginPlay()
{
	Super::BeginPlay();

	PrepareInteractables();
}

void ALyrePuzzle::ScheduleSuccessSound()
{
	GetWorldTimerManager().ClearTimer(PuzzleFeedbackTimerHandle);
	GetWorldTimerManager().SetTimer(PuzzleFeedbackTimerHandle, this, &ALyrePuzzle::PlaySuccessSound, PlaySoundAfterSeconds, false);
}

void ALyrePuzzle::ScheduleFailSound()
{
	GetWorldTimerManager().ClearTimer(PuzzleFeedbackTimerHandle);
	GetWorldTimerManager().SetTimer(PuzzleFeedbackTimerHandle, this, &ALyrePuzzle::PlayFailSound, PlaySoundAfterSeconds, false);
}

void ALyrePuzzle::PlaySound(USoundCue* Sound) const
{
	if (Sound)
	{
		const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (Player)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				Sound,
				Player->GetActorLocation(),
				Player->GetActorRotation()
			);
		}
	}
}

void ALyrePuzzle::PlaySuccessSound()
{
	PlaySound(SuccessSound);
}

void ALyrePuzzle::PlayFailSound()
{
	PlaySound(FailSound);
}

void ALyrePuzzle::DisableAllInteractables()
{
	for (AInteractableBase* Interactable : Interactables)
	{
		Interactable->DisableInteraction();
	}
}

void ALyrePuzzle::EnableAllInteractables()
{
	for (AInteractableBase* Interactable : Interactables)
	{
		Interactable->EnableInteraction();
	}
}

void ALyrePuzzle::PrepareInteractables()
{
	for (AInteractableBase* Interactable : Interactables)
	{
		Interactable->OnInteractionSuccess.AddDynamic(this, &ALyrePuzzle::Interaction);
	}
}

void ALyrePuzzle::HandleSuccess()
{
	DisableAllInteractables();
	ScheduleSuccessSound();
	MarkAsCompleted();
	OnSuccessPuzzle();
}

void ALyrePuzzle::HandleFail()
{
	CurrentPuzzleIndex = 0;
	SuccessInteractions = 0;
	EnableAllInteractables();
	ScheduleFailSound();
	OnFailPuzzle();
}

void ALyrePuzzle::Interaction(AActor* InteractableActor, AActor* ActorInstigator)
{
	AInteractableBase* Interactable = Cast<AInteractableBase>(InteractableActor);
	if (Interactable)
	{
		if (Interactables.IsValidIndex(CurrentPuzzleIndex))
		{
			if (Interactables[CurrentPuzzleIndex] == InteractableActor)
			{
				SuccessInteractions++;
			}

			Interactable->DisableInteraction();
			CurrentPuzzleIndex++;
			OnInteraction(Interactable);		
		}
	}

	if (CurrentPuzzleIndex >= Interactables.Num())
	{
		if (SuccessInteractions == Interactables.Num())
		{
			HandleSuccess();
		}
		else
		{
			HandleFail();
		}
	}
}

FString ALyrePuzzle::GetObjectiveTitle() const
{
	return ObjectiveTitle;
}

FText ALyrePuzzle::GetObjectiveDescription() const
{
	return ObjectiveDescription;
}

void ALyrePuzzle::ActivateObjective()
{
	EnableAllInteractables();
}

void ALyrePuzzle::DeactivateObjective()
{
	DisableAllInteractables();
}

bool ALyrePuzzle::IsObjectiveCompleted()
{
	return bIsCompleted;
}

void ALyrePuzzle::MarkAsCompleted()
{
	bIsCompleted = true;
	OnObjectiveCompleted.Broadcast(this);
}

// Called every frame
void ALyrePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

