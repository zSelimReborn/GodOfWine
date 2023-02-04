// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "SpartanBase.generated.h"

class AGrape;
class UArrowComponent;

UCLASS()
class MYPROJECT4_API ASpartanBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpartanBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetCollectedGrapes() const { return CollectedGrapes; }
	void CollectGrape();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollectGrape();

	void ThrowGrape();

	UFUNCTION(BlueprintImplementableEvent)
	void OnThrowGrape();

// Interactable functions
public:
	void StartInteraction();
	void EndInteraction();
	
	void SetOverlappingInteractableObject(AActor* Interactable);
	void ResetOverlappingInteractableObject(AActor* Interactable);
	
protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UArrowComponent> ThrowGrapeSpawnLocation;
	
	UPROPERTY(Transient)
	TScriptInterface<IInteractable> OverlappingInteractableObject = nullptr;

	UPROPERTY(Transient)
	int32 CollectedGrapes = 0;

	UPROPERTY(EditAnywhere, Category="Throw Grape")
	TSubclassOf<AGrape> GrapeClass;
};
