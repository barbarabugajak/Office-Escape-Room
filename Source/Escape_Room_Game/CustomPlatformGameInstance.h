// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "CustomPlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_GAME_API UCustomPlatformGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
		bool HasKey = false;

};
