// Copyright Epic Games, Inc. All Rights Reserved.

#include "Escape_Room_GamePickUpComponent.h"

UEscape_Room_GamePickUpComponent::UEscape_Room_GamePickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UEscape_Room_GamePickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UEscape_Room_GamePickUpComponent::OnSphereBeginOverlap);
}

void UEscape_Room_GamePickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AEscape_Room_GameCharacter* Character = Cast<AEscape_Room_GameCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
