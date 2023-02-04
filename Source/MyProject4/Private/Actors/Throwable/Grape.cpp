// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Throwable/Grape.h"

// Sets default values
AGrape::AGrape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(DefaultSceneComponent);
}

// Called when the game starts or when spawned
void AGrape::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrape::Throw(const FVector& Direction)
{
	const FVector ImpulseDirection = Direction * ThrowImpulse;
	MeshComponent->AddImpulse(ImpulseDirection);
}

