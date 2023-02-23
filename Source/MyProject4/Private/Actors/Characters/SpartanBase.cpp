// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/SpartanBase.h"

#include "Actors/Throwable/Grape.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASpartanBase::ASpartanBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThrowGrapeSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Throw Grape Spawn Location"));
	ThrowGrapeSpawnLocation->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASpartanBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpartanBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpartanBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ASpartanBase::StartInteraction);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ASpartanBase::EndInteraction);

	PlayerInputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &ASpartanBase::ThrowGrape);
}

void ASpartanBase::CollectGrape()
{
	CollectedGrapes++;

	OnCollectGrape();
}

void ASpartanBase::ThrowGrape()
{
	if (CollectedGrapes > 0)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		CollectedGrapes--;
		AGrape* NewGrape = GetWorld()->SpawnActor<AGrape>(
			GrapeClass,
			ThrowGrapeSpawnLocation->GetComponentLocation(),
			ThrowGrapeSpawnLocation->GetComponentRotation(),
			SpawnParameters
		);

		if (NewGrape)
		{
			const FVector Direction = GetControlRotation().Vector();
			NewGrape->Throw(Direction);
			OnThrowGrape();
		}
	}
}

void ASpartanBase::FocusOnActor(ACameraActor* NewCamera, const float& TimeToFocus, const float& _TotalTimeFocus)
{
	if (NewCamera)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->SetViewTargetWithBlend(NewCamera, TimeToFocus);
			GetCharacterMovement()->Deactivate();
			TotalTimeFocus = _TotalTimeFocus;
			GetWorldTimerManager().SetTimer(ResetFocusTimer, this, &ASpartanBase::FocusOnActorCompleted, TimeToFocus, false);
		}
	}
}

void ASpartanBase::FocusOnActorCompleted()
{
	GetWorldTimerManager().SetTimer(ResetFocusTimer, this, &ASpartanBase::RestorePlayerControl, TotalTimeFocus, false);
}

void ASpartanBase::RestorePlayerControl()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->SetViewTargetWithBlend(this, 1.f);	
	}
	
	GetCharacterMovement()->Activate();
}

void ASpartanBase::StartInteraction()
{
	if (OverlappingInteractableObject)
	{
		OverlappingInteractableObject->StartInteraction(this);
	}
}

void ASpartanBase::EndInteraction()
{
	if (OverlappingInteractableObject)
	{
		OverlappingInteractableObject->EndInteraction(this);
	}
}

void ASpartanBase::SetOverlappingInteractableObject(AActor* Interactable)
{
	if (Interactable == nullptr || !UKismetSystemLibrary::DoesImplementInterface(Interactable, UInteractable::StaticClass()))
	{
		return;
	}
	
	if (OverlappingInteractableObject)
	{
		OverlappingInteractableObject->HideInteractWidget();
	}

	OverlappingInteractableObject = Interactable;
	if (OverlappingInteractableObject->CanInteract())
	{
		OverlappingInteractableObject->ShowInteractWidget();
	}
}

void ASpartanBase::ResetOverlappingInteractableObject(AActor* Interactable)
{
	if (Interactable == nullptr || !UKismetSystemLibrary::DoesImplementInterface(Interactable, UInteractable::StaticClass()))
	{
		return;
	}

	if (OverlappingInteractableObject == Interactable)
	{
		OverlappingInteractableObject->HideInteractWidget();
		OverlappingInteractableObject = nullptr;
	}
}

