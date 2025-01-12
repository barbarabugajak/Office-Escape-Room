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
	
	// Create and configure the box component for detecting overlap
	DoorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBox"));
	DoorBox->SetupAttachment(DoorFrame);
	DoorBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	DoorBox->SetBoxExtent(FVector(150.0f, 75.0f, 250.0f));

	// Enable overlap events for the box component
	DoorBox->SetGenerateOverlapEvents(true);
	DoorBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	DoorBox->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
	
	// Initialize the door state
	bIsPlayerNear = false;
	bIsDoorOpen = false;

	// Scale the whole component
	DoorFrame -> SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
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

// Called when an overlap begins
void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Mark the player as near the door
	bIsPlayerNear = true;

	// Bind only when might be used to prevent bugs
	// Bind Input (0, since there is only one player)
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	EnableInput(PC);

	// Bind the input action to handle door interaction
	InputComponent->BindAction("Interact", IE_Pressed, this, &ADoor::HandleInput); // Bound in engine
}

// Called when an overlap ends
void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Mark the player as far from the door
	bIsPlayerNear = false;

	if (bIsDoorOpen)
	{
		// Close the door if it was open and the player leaves the area
		bIsDoorOpen = false;
		DoorMesh->SetRelativeRotation(FRotator(0, 0, 0));
	}
}

// Handles the player's input to open/close the door
void ADoor::HandleInput()
{
	// Ensure the player is near the door before allowing interaction
	if (bIsPlayerNear)
	{
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
}