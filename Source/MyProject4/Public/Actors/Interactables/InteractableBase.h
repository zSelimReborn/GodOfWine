// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "InteractableBase.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class MYPROJECT4_API AInteractableBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PrepareTrigger();

	UFUNCTION()
	void OnEnterTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLeaveTriggerVolume(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteraction();
	
// Interactable interface
public:
	virtual void EnableInteraction() override;
	virtual void DisableInteraction() override;
	virtual bool CanInteract() const override;
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;
	virtual void StartInteraction(AActor* InteractionInstigator) override;
	virtual void EndInteraction(AActor* InteractionInstigator) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Components
protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UWidgetComponent> InteractWidgetComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USphereComponent> TriggerVolume;
	
	UPROPERTY(Transient)
	bool bInteractionEnabled = true;
};
