// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyTipHUD.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"

AKeyTipHUD::AKeyTipHUD()
{
	// Set the default font
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Game/Office/RobotoMono-VariableFont_wght_Font.RobotoMono-VariableFont_wght_Font"));
	HUDFont = Font.Object;

	bShowInteractMessage = false;
}

void AKeyTipHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bShowInteractMessage && HUDFont)
	{
		FText InteractText = FText::FromString(HUDText);
		FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
		FVector2D TextDimensions;

		// Get text size (optional, but useful for centering)
		Canvas->StrLen(HUDFont, InteractText.ToString(), TextDimensions.X, TextDimensions.Y);

		// Position text
		FVector2D TextPosition = FVector2D(
		(ScreenDimensions.X - TextDimensions.X) / 2, // Center horizontally
		ScreenDimensions.Y - TextDimensions.Y - 50 // Move to bottom (50 pixels above bottom edge)
		);


		// Customize text appearance
		FCanvasTextItem TextItem(TextPosition, InteractText, HUDFont, FLinearColor::Black); // Change color here
		TextItem.Scale = FVector2D(1.0f, 1.0f);
		TextItem.FontRenderInfo.bEnableShadow = true; // Optional: Enables shadow for better visibility
		TextItem.bOutlined = true; 
		TextItem.bCentreX = true; // Center horizontally
		TextItem.bCentreY = true; // Center vertically

		// Draw the text on the canvas
		Canvas->DrawItem(TextItem);
	}
}

void AKeyTipHUD::ShowInteractMessage(bool bShow)
{
	bShowInteractMessage = bShow;
}

void AKeyTipHUD::SetText(FString text)
{
	HUDText = text;
}

