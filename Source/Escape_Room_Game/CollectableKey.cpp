// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableKey.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "UserTipsWidget.h"


// Sets default values
ACollectableKey::ACollectableKey()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box collision component to detect overlaps and set it as the root.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	RootComponent = BoxComponent;

	// Create the mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	// Source: https://sketchfab.com/3d-models/key-with-tag-16ea3fbecc6346df9859f0e18406951b
	static ConstructorHelpers::FObjectFinder<UStaticMesh> KeyMesh(TEXT("/Game/Office/SM_Key.SM_Key"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MetalOrbMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Chrome.M_Metal_Chrome")); //From starter content

	// Set the orb's static mesh and material if the assets were loaded successfully
	if (KeyMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(KeyMesh.Object);
		// Scale the key
		if (MetalOrbMaterial.Succeeded())
		{
			StaticMesh->SetMaterial(0, MetalOrbMaterial.Object);
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Orb Mesh could not be found"));
	}
	if (Opens != nullptr)
	{
		// Enable overlap events for the box component and bind the overlap event to a handler
		// BoxComponent->SetGenerateOverlapEvents(true);
		// Add a response to overlapping
		// BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectableKey::OnBeginOverlap);
	}

	// Scale the component
	GetRootComponent()->SetWorldScale3D(FVector(8.0f, 8.0f, 8.0f));
	
}
	


// Called when the game starts or when spawned
void ACollectableKey::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("CanBeLookedAtByPlayer"));
	
	
}

// Called every frame
void ACollectableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectableKey::OnInteract()
{
	UE_LOG(LogTemp, Display, TEXT("OnInteract"));

	if (Opens && Opens->IsValidLowLevel())
	{
		Opens->SetHasKey(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Opens reference in OnInteract!"));
	}

	Destroy();
}

void ACollectableKey::OnLookedAt_Implementation(AActor* LookingActor)
{
	if (!LookingActor) 
	{
		UE_LOG(LogTemp, Warning, TEXT("LookingActor is nullptr!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("The Key is being looked at by %s"), *LookingActor->GetName());

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

		InputComponent->BindAction("Interact", IE_Pressed, this, &ACollectableKey::OnInteract);
	}
}

