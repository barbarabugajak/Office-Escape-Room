// Copyright Epic Games, Inc. All Rights Reserved.

#include "Escape_Room_GameCharacter.h"
#include "Escape_Room_GameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "SNegativeActionButton.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/IHttpResponse.h"
#include "LookableInterface.h"
#include "Net/NetworkMetricsDefs.h"
#include "UObject/TemplateString.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AEscape_Room_GameCharacter

AEscape_Room_GameCharacter::AEscape_Room_GameCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("Character is created"));
	// To check looking at stuff
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	GetRootComponent() -> SetWorldScale3D(FVector(0.5f, 0.5f, 2.0f));
}

//////////////////////////////////////////////////////////////////////////// Input

void AEscape_Room_GameCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AEscape_Room_GameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEscape_Room_GameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEscape_Room_GameCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AEscape_Room_GameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEscape_Room_GameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEscape_Room_GameCharacter::IsLookingAt()
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null"));
		return;
	}

	// Raycasting (Line Trace by Object)
	UWorld * CurrentWorld = GetWorld();
	FHitResult ActorHit;
	FVector RayStart = this->GetActorLocation();
	// Line trace from player's current location to a point 1000 ahead of it
	FVector RayEnd = RayStart + GetControlRotation().Vector() * 1000.f; // Ensure proper distance
	// Prevent from hitting self
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);

	FCollisionResponseParams ResponseParameters;

	// Perform raycasting
	CurrentWorld->LineTraceSingleByChannel(ActorHit, RayStart, RayEnd, ECC_Visibility,  CollisionParameters, ResponseParameters);
	
	if (ActorHit.GetActor() != nullptr)
	{
		AActor* Actor = Cast<AActor>(ActorHit.GetActor());
		if (Actor != nullptr)
		{
			// Don't interact with all actors
			if (Actor->Tags.Contains("CanBeLookedAtByPlayer"))
			{
				UE_LOG(LogTemp, Display, TEXT("Looking at %s"), *Actor->GetName());

			}
			
		}
	}

	
	// For debugging purposes
	DrawDebugLine(CurrentWorld, RayStart, RayEnd, FColor(255, 0,0 ));
}

void AEscape_Room_GameCharacter::Tick(float DeltaTime)
{
	IsLookingAt();
}