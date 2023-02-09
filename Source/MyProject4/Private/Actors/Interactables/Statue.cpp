// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Statue.h"

#include "Subsystems/ObjectiveSubsystem.h"

void AStatue::BeginPlay()
{
	Super::BeginPlay();

	const UObjectiveSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UObjectiveSubsystem>();
	if (ObjectiveSubsystem)
	{
		if (ObjectiveSubsystem->IsAnObjectiveQueued(this))
		{
			DisableInteraction();
		}
	}
}

void AStatue::Interaction(AActor* InteractionInstigator)
{
	if (!CanInteract())
	{
		return;	
	}
	
	UE_LOG(LogTemp, Display, TEXT("AStatue::Interaction to implement."));
	MarkAsCompleted();
	DisableInteraction();
	HideInteractWidget();
	OnObjectiveCompleted.Broadcast(this);
}

bool AStatue::CanInteract() const
{
	return Super::CanInteract();
}

void AStatue::StartInteraction(AActor* InteractionInstigator)
{
	Interaction(InteractionInstigator);
}

void AStatue::EndInteraction(AActor* InteractionInstigator)
{
	Super::EndInteraction(InteractionInstigator);
}

FString AStatue::GetObjectiveTitle() const
{
	return ObjectiveTitle;
}

FText AStatue::GetObjectiveDescription() const
{
	return ObjectiveDescription;
}

void AStatue::ActivateObjective()
{
	EnableInteraction();
}

bool AStatue::IsObjectiveCompleted()
{
	return bIsObjectiveCompleted;
}

void AStatue::MarkAsCompleted()
{
	bIsObjectiveCompleted = true;
}
