// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Throwable.h"
#include "Grape.generated.h"

UCLASS()
class MYPROJECT4_API AGrape : public AActor, public IThrowable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrape();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Throwable Interface
public:
	virtual void Throw(const FVector& Direction) override;

// Components
protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category="Throw Grape")
	float ThrowImpulse = 5000.f;
};
