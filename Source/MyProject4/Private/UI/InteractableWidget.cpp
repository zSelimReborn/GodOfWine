// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractableWidget.h"

#include "Components/TextBlock.h"

FString UInteractableWidget::GetInteractText() const
{
	return InteractText->GetText().ToString();
}

void UInteractableWidget::SetInteractText(const FString& NewInteractText)
{
	if (!NewInteractText.IsEmpty())
	{
		InteractText->SetText(FText::FromString(NewInteractText));
	}
	else
	{
		ResetInteractText();
	}
}

FString UInteractableWidget::GetDefaultInteractText() const
{
	return TEXT("Interact");
}

void UInteractableWidget::ResetInteractText()
{
	InteractText->SetText(FText::FromString(GetDefaultInteractText()));
}
