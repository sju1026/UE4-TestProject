// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyTestGameGameModeBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState :uint8
{
	GameStart,
	GamePlay,
	GamePause,
	GameOver,
};

UCLASS()
class MYTESTGAME_API AMyTestGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "UMG Game")
		EGameState gameStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* currentWidget;

public:
	AMyTestGameGameModeBase();

	void ChangeUI();
};
