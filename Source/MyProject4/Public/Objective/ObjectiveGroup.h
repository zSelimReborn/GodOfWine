// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Objective.h"
#include "ObjectiveGroup.generated.h"


UCLASS()
class MYPROJECT4_API AObjectiveGroup : public AActor, public IObjective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PrepareObjectivesArray();

	UFUNCTION()
	void ObjectiveCompleted(AActor* ObjectiveActor);
	
	void PrepareObjectiveCompletedDelegate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// IObjective interface
public:
	virtual FString GetObjectiveTitle() const override;
	virtual FText GetObjectiveDescription() const override;
	virtual void ActivateObjective() override;
	virtual bool IsObjectiveCompleted() override;
	virtual void MarkAsCompleted() override;

protected:
	UPROPERTY(EditAnywhere, Category="Objective")
	FString ObjectiveTitle;

	UPROPERTY(EditAnywhere, Category="Objective")
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, Category="Objective")
	TArray<TObjectPtr<AActor>> ObjectiveActors;

	UPROPERTY(Transient)
	TArray<TScriptInterface<IObjective>> Objectives;

	UPROPERTY(Transient)
	bool bIsCompleted;
};
