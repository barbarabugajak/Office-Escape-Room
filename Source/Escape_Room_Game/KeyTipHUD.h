#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KeyTipHUD.generated.h"

UCLASS()
class ESCAPE_ROOM_GAME_API AKeyTipHUD : public AHUD
{
	GENERATED_BODY()

public:
	AKeyTipHUD();

	virtual void DrawHUD() override; // Ensure this is correctly declared

	void ShowInteractMessage(bool bShow);

private:
	UPROPERTY()
	UFont* HUDFont;

	bool bShowInteractMessage;
};
