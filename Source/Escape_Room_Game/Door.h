// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "LookableInterface.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

// Delegate to broadcast door opening events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoorSignature);

UCLASS()
class ESCAPE_ROOM_GAME_API ADoor : public AActor, public ILookableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh component - the door
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	// Static mesh component - frame of the door
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorFrame;

	// Box component used for detecting overlap events
	UPROPERTY(EditAnywhere)
	UBoxComponent* DoorBox;

	// Tracks whether the door is open
	UPROPERTY(EditAnywhere)
	bool bIsDoorOpen;

	// Interface
	virtual void OnLookedAt_Implementation(AActor* LookingActor) override;

	// Handle the keyboard input
	virtual void OnInteract();
};
