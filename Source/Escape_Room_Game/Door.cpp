// Fill out your copyright notice in the Description page of Project Settings.
#include "Door.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create and configure the door frame mesh as the root component
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;
	// Create and configure the door mesh, attaching it to the door frame
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorFrame);

	// Load and assign the door mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorMeshObject(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));
	
	if (DoorMeshObject.Succeeded())
	{
		DoorMesh->SetStaticMesh(DoorMeshObject.Object);
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("DoorMesh could not be found"));
	}

	// Load and assign the door frame mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorFrameMeshObject(TEXT("/Game/StarterContent/Props/SM_DoorFrame.SM_DoorFrame"));

	if (DoorFrameMeshObject.Succeeded())
	{
		
		DoorFrame-> SetStaticMesh(DoorFrameMeshObject.Object);
		DoorFrame -> SetCollisionProfileName(TEXT("BlockAll"));

	} else
	{
		UE_LOG(LogTemp, Error, TEXT("DoorFrame could not be found"));
	}

	// Position the door relative to the door frame
	DoorMesh->SetRelativeLocation(FVector(6.0f, 45.0f, 0.0f));
	
	// Initialize the door state
	bIsDoorOpen = false;

	// Scale the whole component
	DoorFrame -> SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));

	// Allow LookableInterface
	Tags.Add(TEXT("CanBeLookedAtByPlayer"));
}
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnLookedAt_Implementation(AActor* LookingActor)
{
	if (!LookingActor) 
	{
		UE_LOG(LogTemp, Warning, TEXT("LookingActor is nullptr!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("The Door is being looked at by %s"), *LookingActor->GetName());

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		EnableInput(PC);

		if (!InputComponent)
		{
			InputComponent = NewObject<UInputComponent>(this, TEXT("KeyInputComponent"));
			InputComponent->RegisterComponent();
			this->AddOwnedComponent(InputComponent); // Ensures proper lifecycle management
		}

		InputComponent->BindAction("Interact", IE_Pressed, this, &ADoor::OnInteract);
	}
	
}

// Handles the player's input to open/close the door
void ADoor::OnInteract() {
	
		// Close the door if it's open
		if (bIsDoorOpen)
		{
			bIsDoorOpen = false;
			DoorMesh->SetRelativeRotation(FRotator(0, 0, 0));
		}
		// Open the door if it's closed
		else
		{
			bIsDoorOpen = true;
			DoorMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f), true);
		}
}