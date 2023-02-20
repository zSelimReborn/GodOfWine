// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/SpartanBase.h"

#include "Actors/Throwable/Grape.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	InternalCameraBoom = FindComponentByClass<USpringArmComponent>();
	if (InternalCameraBoom)
	{
		CameraBoomRelativeLocation = InternalCameraBoom->GetRelativeLocation();
	}
	
	InternalFollowCamera = FindComponentByClass<UCameraComponent>();
	if (InternalFollowCamera)
	{
		InitialFOV = InternalFollowCamera->FieldOfView;
	}
}

void ASpartanBase::FocusCamera(const float& DeltaTime)
{
	if (InternalFollowCamera && FocusActor.bIsActive)
	{
		CurrentFocusTime += DeltaTime;
	}
	else
	{
		CurrentFocusTime = FMath::Max(0.f, CurrentFocusTime - DeltaTime);
	}

	const float MoveAlpha = FMath::Clamp(CurrentFocusTime / FocusActor.TimeToFocus, 0.f, 1.f);
	const float NewFOV = FMath::Lerp(InitialFOV, FocusActor.DesiredFOV, MoveAlpha);

	if (InternalFollowCamera)
	{
		InternalFollowCamera->FieldOfView = NewFOV;
	}
}

// Called every frame
void ASpartanBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FocusCamera(DeltaTime);
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

void ASpartanBase::FocusOnActor(AActor* ActorToFocus, const float& NewFov, const float& TimeToFocus, const float& TotalTimeToFocus, const FVector& NewCameraLocation)
{
	if (InternalCameraBoom && ActorToFocus)
	{
		FocusActor.Actor = ActorToFocus;
		FocusActor.bIsActive = true;
		FocusActor.DesiredFOV = NewFov;
		FocusActor.TimeToFocus = TimeToFocus;
		FocusActor.TotalFocusTime = TotalTimeToFocus;
		
		const FVector DirectionToActor = ActorToFocus->GetActorLocation() - GetActorLocation();
		const FRotator RotationToActor = DirectionToActor.Rotation();

		InternalCameraBoom->bInheritYaw = false;
		InternalCameraBoom->bUsePawnControlRotation = false;
		GetCharacterMovement()->Deactivate();
		
		const FLatentActionInfo ActionInfo{INDEX_NONE, INDEX_NONE, nullptr, this};
		UKismetSystemLibrary::MoveComponentTo(InternalCameraBoom, NewCameraLocation, RotationToActor, true,
		true, TimeToFocus, false, EMoveComponentAction::Move, ActionInfo);

		GetWorldTimerManager().SetTimer(ResetFocusTimer, this, &ASpartanBase::RestoreFocus, TotalTimeToFocus/2, false);
	}
}

void ASpartanBase::RestoreFocus()
{
	if (InternalCameraBoom && FocusActor.Actor)
	{
		GetWorldTimerManager().SetTimer(ResetFocusTimer, this, &ASpartanBase::RestorePlayerControl, FocusActor.TotalFocusTime/2, false);
		
		FocusActor.Actor = nullptr;
		FocusActor.bIsActive = false;
		FocusActor.TimeToFocus = 1.f;
	}
}

void ASpartanBase::RestorePlayerControl()
{
	if (InternalCameraBoom)
	{
		InternalCameraBoom->SetRelativeLocation(CameraBoomRelativeLocation);
		InternalCameraBoom->bUsePawnControlRotation = true;
		InternalCameraBoom->bInheritYaw = true;
		GetCharacterMovement()->Activate();
	}
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

