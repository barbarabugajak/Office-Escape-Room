#include "LockedDoor.h"
#include "Components/RectLightComponent.h"

ALockedDoor::ALockedDoor()
{
	LockedDoor_RectLight = CreateDefaultSubobject<URectLightComponent>("LockedDoor_RectLight");
	LockedDoor_RectLight->SetLightColor(FColor::Red);
	LockedDoor_RectLight->AddRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	LockedDoor_RectLight->SetupAttachment(GetRootComponent());

	// To enable usage of ILookableInterface
	Tags.Add(TEXT("CanBeLookedAtByPlayer"));
}

void ALockedDoor::BeginPlay()
{
	Super::BeginPlay();
	HasKey = false;
}

void ALockedDoor::SetHasKey(bool bCanOpen)
{
	HasKey = bCanOpen;
	if (HasKey)
	{
		LockedDoor_RectLight->SetLightColor(FColor::Green);
	}
}

void ALockedDoor::OnInteract()
{
	// Ensure the player is near the door and the door has the key before interaction
		if (HasKey == true)
		{
			// Open or close the door based on the current state
			if (bIsDoorOpen)
			{
				bIsDoorOpen = false;
				DoorMesh->SetRelativeRotation(FRotator(0, 0, 0));
			}
			else
			{
				bIsDoorOpen = true;
				DoorMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f), true);
			}
		} else
		{
			bIsDoorOpen = false;
			UE_LOG(LogTemp, Warning, TEXT("Locked Door"));
		}
	
}
