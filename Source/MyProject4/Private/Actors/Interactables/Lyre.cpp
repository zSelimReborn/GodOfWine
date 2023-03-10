// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Lyre.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ALyre::ALyre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALyre::BeginPlay()
{
	Super::BeginPlay();
}

void ALyre::Interaction(AActor* InstigatorActor)
{
	if (!CanInteract())
	{
		return;
	}
	
	if (LyreMusic)
	{
		const float PitchMultiplier = FMath::RandRange(MinPitchMultiplier, MaxPitchMultiplier);
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			LyreMusic,
			GetActorLocation(),
			GetActorRotation(),
			1.f,
			PitchMultiplier,
			StartMusicTime
		);

		bHasBeenPlayed = true;
		HideInteractWidget();
	}

	OnInteractionSuccess.Broadcast(this, InstigatorActor);
	OnInteraction();
}

// Called every frame
void ALyre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALyre::EnableInteraction()
{
	Super::EnableInteraction();
	bHasBeenPlayed = false;
}

void ALyre::DisableInteraction()
{
	Super::DisableInteraction();
	bHasBeenPlayed = false;
}

bool ALyre::CanInteract() const
{
	return !bHasBeenPlayed && Super::CanInteract();
}

void ALyre::StartInteraction(AActor* InteractionInstigator)
{
	Interaction(InteractionInstigator);
}

void ALyre::EndInteraction(AActor* InteractionInstigator)
{
}

