// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" // Import the Box component 
#include "LockedDoor.h"
#include "LookableInterface.h" // For interface handling
#include "CollectableKey.generated.h"

UCLASS()
class ESCAPE_ROOM_GAME_API ACollectableKey : public AActor, public ILookableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Static mesh component representing the platform's visual appearance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	// Box component that detects the overlapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALockedDoor* Opens; // Reference to what the key opens

	UFUNCTION()
	void OnInteract();

	virtual void OnLookedAt_Implementation(AActor* LookingActor) override;
};
