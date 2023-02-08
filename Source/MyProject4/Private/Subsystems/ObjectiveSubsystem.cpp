// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ObjectiveSubsystem.h"

#include "Interfaces/Objective.h"
#include "Kismet/KismetSystemLibrary.h"

void UObjectiveSubsystem::ObjectiveCompleted(AActor* ObjectiveActor)
{
	OnObjectiveCompleted.Broadcast(ObjectiveActor);

	CurrentObjectiveIndex++;
	ActivateCurrentObjective();
	if (CurrentObjectiveIndex >= Objectives.Num())
	{
		FireObjectivesCompletedEvent();
	}
}

void UObjectiveSubsystem::ActivateCurrentObjective()
{
	if (Objectives.IsValidIndex(CurrentObjectiveIndex))
    {
    	AActor* CurrentObjective = Cast<AActor>(Objectives[CurrentObjectiveIndex].GetObject());
    	if (CurrentObjective)
    	{
    		Objectives[CurrentObjectiveIndex]->ActivateObjective();
    		OnObjectiveActivated.Broadcast(CurrentObjective);
    	}
    }
}

void UObjectiveSubsystem::AddObjective(AActor* ObjectiveActor)
{
	if (ObjectiveActor->GetClass()->ImplementsInterface(UObjective::StaticClass()))
	{
		const int NewIndex = Objectives.Add(ObjectiveActor);
		Objectives[NewIndex]->OnObjectiveCompleted.AddUniqueDynamic(this, &UObjectiveSubsystem::ObjectiveCompleted);
	}
}

FString UObjectiveSubsystem::GetCurrentObjectiveTitle() const
{
	if (Objectives.IsValidIndex(CurrentObjectiveIndex))
	{
		return Objectives[CurrentObjectiveIndex]->GetObjectiveTitle();
	}

	return TEXT("N/A");
}

FText UObjectiveSubsystem::GetCurrentObjectiveDescription() const
{
	if (Objectives.IsValidIndex(CurrentObjectiveIndex))
	{
		return Objectives[CurrentObjectiveIndex]->GetObjectiveDescription();
	}

	return FText::FromString(TEXT("N/A"));
}

void UObjectiveSubsystem::FireObjectivesCompletedEvent()
{
	OnAllObjectivesCompleted.Broadcast();
}

void UObjectiveSubsystem::OnMapStart()
{
	ActivateCurrentObjective();
}
