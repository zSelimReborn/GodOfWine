// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/InteractableBase.h"

#include "Actors/Characters/SpartanBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/InteractableWidget.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(DefaultSceneComponent);

	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget Component"));
	InteractWidgetComponent->SetupAttachment(DefaultSceneComponent);

	TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetupAttachment(DefaultSceneComponent);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
	HideInteractWidget();
	// No highlight post process
	DisableCustomDepth();

	if (InteractWidgetComponent)
	{
		UInteractableWidget* _InteractableWidget = Cast<UInteractableWidget>(InteractWidgetComponent->GetUserWidgetObject());
		if (_InteractableWidget)
		{
			InteractableWidgetRef = _InteractableWidget;
		}
	}
}

void AInteractableBase::PrepareTrigger()
{
	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::OnEnterTriggerVolume);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnLeaveTriggerVolume);
	}
}

void AInteractableBase::OnEnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
	{
		return;
	}

	ASpartanBase* Character = Cast<ASpartanBase>(OtherActor);
	if (Character)
	{
		Character->SetOverlappingInteractableObject(this);
	}
}

void AInteractableBase::OnLeaveTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr)
	{
		return;
	}

	ASpartanBase* Character = Cast<ASpartanBase>(OtherActor);
	if (Character)
	{
		Character->ResetOverlappingInteractableObject(this);
	}
}

void AInteractableBase::EnableCustomDepth()
{
	if (!CanInteract())
	{
		return;
	}

	TArray<TObjectPtr<UMeshComponent>> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);
	for (UMeshComponent* Component : MeshComponents)
	{
		if (Component)
		{
			Component->SetRenderCustomDepth(true);
		}
	}
}

void AInteractableBase::DisableCustomDepth()
{
	TArray<TObjectPtr<UMeshComponent>> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);
	for (UMeshComponent* Component : MeshComponents)
	{
		if (Component)
		{
			Component->SetRenderCustomDepth(false);
		}
	}
}

void AInteractableBase::EnableInteraction()
{
	bInteractionEnabled = true;
}

void AInteractableBase::DisableInteraction()
{
	bInteractionEnabled = false;
}

bool AInteractableBase::CanInteract() const
{
	return bInteractionEnabled;
}

void AInteractableBase::ShowInteractWidget()
{
	if (InteractWidgetComponent)
	{
		InteractWidgetComponent->SetVisibility(true);
		if (InteractableWidgetRef)
		{
			InteractableWidgetRef->SetInteractText(InteractWidgetString);
		}

		EnableCustomDepth();
	}
}

void AInteractableBase::HideInteractWidget()
{
	if (InteractWidgetComponent)
	{
		InteractWidgetComponent->SetVisibility(false);
		if (InteractableWidgetRef)
		{
			InteractableWidgetRef->ResetInteractText();
		}

		DisableCustomDepth();
	}
}

void AInteractableBase::StartInteraction(AActor* InteractionInstigator)
{
	// To implement in child classes
}

void AInteractableBase::EndInteraction(AActor* InteractionInstigator)
{
	// To implement in child classes
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

