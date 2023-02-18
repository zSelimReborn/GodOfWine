// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "SpartanBase.generated.h"

class AGrape;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;

USTRUCT()
struct FFocusActor
{
	GENERATED_BODY()

	TObjectPtr<AActor> Actor = nullptr;
	bool bIsActive = false;
	float DesiredFOV = 100.f;
	float TimeToFocus = 1.f;
	float TotalFocusTime = 5.f;
};

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

	void FocusCamera(const float& DeltaTime);
	
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

	UFUNCTION(BlueprintCallable)
	void FocusOnActor(AActor* ActorToFocus, const float& NewFov, const float& TimeToFocus, const float& TotalTimeToFocus, const FVector& NewCameraLocation);

	UFUNCTION(BlueprintCallable)
	void RestoreFocus();

	void RestorePlayerControl();
	
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

	UPROPERTY(Transient)
	FFocusActor FocusActor;

	UPROPERTY(Transient)
	TObjectPtr<USpringArmComponent> InternalCameraBoom;

	UPROPERTY(Transient)
	TObjectPtr<UCameraComponent> InternalFollowCamera;

	UPROPERTY(Transient)
	float InitialFOV = 90.f;

	UPROPERTY(Transient)
	FVector CameraBoomRelativeLocation;

	UPROPERTY(Transient)
	float CurrentFocusTime = 0.f;

	FTimerHandle ResetFocusTimer;
};
