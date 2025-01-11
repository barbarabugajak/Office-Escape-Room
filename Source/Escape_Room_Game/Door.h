// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

// Delegate to broadcast door opening events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoorSignature);

UCLASS()
class ESCAPE_ROOM_GAME_API ADoor : public AActor
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

	// Tracks whether the player is near the door
	UPROPERTY(EditAnywhere)
	bool bIsPlayerNear;

	// Function to handle beginning of the overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Function to handle the end of the overlap
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Handle the keyboard input
	virtual void HandleInput();
};
