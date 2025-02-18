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

	virtual void DrawHUD() override;

	void ShowInteractMessage(bool bShow);

	FString HUDText;

	void SetText(FString text);

	void SetDidGameEnd(bool DidGameEnd);
	
private:
	UPROPERTY()
	UFont* HUDFont;

	bool bShowInteractMessage;

	bool bDidGameEnd = false;
};
