// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Lattice.h"

#include "Actors/Characters/SpartanBase.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/ObjectiveSubsystem.h"

// Sets default values
ALattice::ALattice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALattice::BeginPlay()
{
	Super::BeginPlay();

	if (GrapesToComplete > MaxGrapes)
	{
		GrapesToComplete = MaxGrapes;
	}
}

void ALattice::Interaction(AActor* InteractionInstigator)
{
	if (!CanInteract())
	{
		return;
	}

	ASpartanBase* Character = Cast<ASpartanBase>(InteractionInstigator);
	if (Character)
	{
		Character->CollectGrape();
		CurrentGrapes--;

		if (CurrentGrapes <= 0)
		{
			HideInteractWidget();
		}

		OnInteraction();
		OnInteractionSuccess.Broadcast(this, InteractionInstigator);

		if (!IsObjectiveCompleted())
		{
			if (Character->GetCollectedGrapes() >= GrapesToComplete)
			{
				MarkAsCompleted();
				OnObjectiveCompleted.Broadcast(this);
			}
		}
	}
}

// Called every frame
void ALattice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALattice::CanInteract() const
{
	return (CurrentGrapes > 0) && Super::CanInteract();
}

void ALattice::StartInteraction(AActor* InteractionInstigator)
{
	Interaction(InteractionInstigator);
}

void ALattice::EndInteraction(AActor* InteractionInstigator)
{
}

FString ALattice::GetObjectiveTitle() const
{
	return ObjectiveTitle;
}

FText ALattice::GetObjectiveDescription() const
{
	return ObjectiveDescription;
}

void ALattice::ActivateObjective()
{
	EnableInteraction();
}

void ALattice::DeactivateObjective()
{
	DisableInteraction();
}

bool ALattice::IsObjectiveCompleted()
{
	return bIsObjectiveCompleted;
}

void ALattice::MarkAsCompleted()
{
	bIsObjectiveCompleted = true;
}
