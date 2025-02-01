// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "Components/RectLightComponent.h"
#include "LockedDoor.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_GAME_API ALockedDoor : public ADoor
{
	GENERATED_BODY()

	public:
		ALockedDoor();
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locked Door")
		bool HasKey = false;

		UPROPERTY(BlueprintReadWrite)
		URectLightComponent* LockedDoor_RectLight;
		
		UFUNCTION(BlueprintCallable, Category = "Locked Door")
		void SetHasKey(bool bCanOpen);
	
		// Handle the keyboard input
		virtual void OnInteract() override;

		// Override beginPlay
		virtual void BeginPlay() override;
};
