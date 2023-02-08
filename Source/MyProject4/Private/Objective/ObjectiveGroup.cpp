// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective/ObjectiveGroup.h"

// Sets default values
AObjectiveGroup::AObjectiveGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectiveGroup::BeginPlay()
{
	Super::BeginPlay();

	PrepareObjectivesArray();
	PrepareObjectiveCompletedDelegate();
}

void AObjectiveGroup::PrepareObjectivesArray()
{
	for (AActor* ObjectiveActor : ObjectiveActors)
	{
		if (ObjectiveActor->GetClass()->ImplementsInterface(UObjective::StaticClass()))
		{
			Objectives.Add(ObjectiveActor);
		}
	}
}

void AObjectiveGroup::ObjectiveCompleted(AActor* ObjectiveActor)
{
	MarkAsCompleted();
	for (const TScriptInterface<IObjective> Objective : Objectives)
	{
		Objective->MarkAsCompleted();
	}

	OnObjectiveCompleted.Broadcast(this);
}

void AObjectiveGroup::PrepareObjectiveCompletedDelegate()
{
	for (const TScriptInterface<IObjective> Objective : Objectives)
	{
		Objective->OnObjectiveCompleted.AddUniqueDynamic(this, &AObjectiveGroup::ObjectiveCompleted);
	}
}

// Called every frame
void AObjectiveGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AObjectiveGroup::GetObjectiveTitle() const
{
	return ObjectiveTitle;
}

FText AObjectiveGroup::GetObjectiveDescription() const
{
	return ObjectiveDescription;
}

void AObjectiveGroup::ActivateObjective()
{
	for (const TScriptInterface<IObjective> Objective : Objectives)
	{
		Objective->ActivateObjective();
	}
}

bool AObjectiveGroup::IsObjectiveCompleted()
{
	return bIsCompleted;
}

void AObjectiveGroup::MarkAsCompleted()
{
	bIsCompleted = true;
}

