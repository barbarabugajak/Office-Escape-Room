// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyTipHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"

AKeyTipHUD::AKeyTipHUD()
{
	// Set the default font
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Game/Office/RobotoMono-VariableFont_wght_Font.RobotoMono-VariableFont_wght_Font"));
	if (Font.Succeeded())
	{
		HUDFont = Font.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load font for HUD!"));
		HUDFont = nullptr;
	}

	bShowInteractMessage = false;
}

void AKeyTipHUD::DrawHUD()
{
	Super::DrawHUD();

	// Ensure we have a valid canvas and font before drawing
	if (!bShowInteractMessage || !Canvas || !HUDFont) 
	{
		return;
	}

	FText InteractText = FText::FromString(HUDText);
	FVector2D ScreenDimensions(Canvas->SizeX, Canvas->SizeY);
	FVector2D TextDimensions;

	// Get text size (optional, but useful for centering)
	Canvas->StrLen(HUDFont, InteractText.ToString(), TextDimensions.X, TextDimensions.Y);

	// Position text in the center horizontally, and near the bottom
	FVector2D TextPosition(
		ScreenDimensions.X * 0.5f, // Center X (bCentreX will align it properly)
		ScreenDimensions.Y - TextDimensions.Y - 50.0f // Move to bottom (50 pixels above edge)
	);

	// Customize text appearance
	FCanvasTextItem TextItem(TextPosition, InteractText, HUDFont, FLinearColor::Black);
	TextItem.Scale = FVector2D(1.0f, 1.0f);
	TextItem.FontRenderInfo.bEnableShadow = true; // Enable shadow for better visibility
	TextItem.bOutlined = true; 
	TextItem.OutlineColor = FLinearColor::White; // Ensures the outline is visible
	TextItem.bCentreX = true; // Center horizontally
	TextItem.bCentreY = true; // Center vertically

	// Draw the text on the canvas
	Canvas->DrawItem(TextItem);
}

void AKeyTipHUD::ShowInteractMessage(bool bShow)
{
	bShowInteractMessage = bShow;
}

void AKeyTipHUD::SetText(FString text)
{
	HUDText = MoveTempIfPossible(text);
}

