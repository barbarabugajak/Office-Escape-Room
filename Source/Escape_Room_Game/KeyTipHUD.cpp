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
	if (bDidGameEnd == false)
	{
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
	} else
	{
		// Ensure we have a valid canvas and font before drawing
		if (!bShowInteractMessage || !Canvas || !HUDFont) 
		{
			return;
		}
		float ScreenX = Canvas->SizeX;
		float ScreenY = Canvas->SizeY;

		// Set fonts (Optional: You can load custom fonts if needed)
		UFont* LargeFont = GEngine->GetLargeFont();
		UFont* HugeFont = GEngine->GetMediumFont(); // Adjust font size here

		// Colors
		FLinearColor GreenColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
		FLinearColor BlackColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black

		// Huge "YOU WIN" Text
		FString WinText = TEXT("YOU WIN");
		float WinTextScale = 4.0f; // Size multiplier
		float WinTextX = ScreenX / 2.0f;
		float WinTextY = ScreenY / 3.0f;

		// Draw black outline first
		float OutlineOffset = 3.0f;
		for (float xOffset = -OutlineOffset; xOffset <= OutlineOffset; xOffset += OutlineOffset)
		{
			for (float yOffset = -OutlineOffset; yOffset <= OutlineOffset; yOffset += OutlineOffset)
			{
				DrawText(WinText, BlackColor, WinTextX + xOffset, WinTextY + yOffset, HugeFont, WinTextScale, false);
			}
		}

		// Draw main green text
		DrawText(WinText, GreenColor, WinTextX, WinTextY, HugeFont, WinTextScale, false);

		// Smaller "You found all the keys" text
		FString FoundKeysText = TEXT("You found all the keys");
		float FoundKeysScale = 2.5f; // Smaller size
		float FoundKeysX = ScreenX / 2.0f;
		float FoundKeysY = WinTextY + 100.0f; // Below "YOU WIN"

		// Draw black outline first
		for (float xOffset = -OutlineOffset; xOffset <= OutlineOffset; xOffset += OutlineOffset)
		{
			for (float yOffset = -OutlineOffset; yOffset <= OutlineOffset; yOffset += OutlineOffset)
			{
				DrawText(FoundKeysText, BlackColor, FoundKeysX + xOffset, FoundKeysY + yOffset, LargeFont, FoundKeysScale, false);
			}
		}

		// Draw main green text
		DrawText(FoundKeysText, GreenColor, FoundKeysX, FoundKeysY, LargeFont, FoundKeysScale, false);
	
	}
}

void AKeyTipHUD::ShowInteractMessage(bool bShow)
{
	bShowInteractMessage = bShow;
}

void AKeyTipHUD::SetText(FString text)
{
	HUDText = MoveTempIfPossible(text);
}


void AKeyTipHUD::SetDidGameEnd(bool DidGameEnd)
{
	bDidGameEnd = DidGameEnd;
}