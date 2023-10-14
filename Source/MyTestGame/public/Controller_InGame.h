// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controller_InGame.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AController_InGame : public APlayerController
{
	GENERATED_BODY()
	
public:
	AController_InGame();

protected:
	void SetupInputComponent()override;

public:
	void ShowGameMenu();
	void CloseGameMenu();
	void ShowDieUI();

	void ShowInventory();

	void ViewMousePointer();
	void ViewMousePointer_Exit();

	/*UFUNCTION(BlueprintCallable, Category = "MyUI")
		void CreateItemSlots();*/

	UFUNCTION(BlueprintCallable, Category = "MyUI")
		void CloseInventory();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isShowGameMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isShowInventory;

	/*TSubclassOf<class UUserWidget>uiItemSlotBPClass;
	UUserWidget* uiItemSlotWidget;*/


private:
	TSubclassOf<class UUserWidget>uiGameBPClass;
	UUserWidget* uiGameWidget;

	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget;

	TSubclassOf<class UUserWidget>uiGameDieBPClass;
	UUserWidget* uiGameDieWidget;

	TSubclassOf<class UUserWidget>uiInventoryBPClass;
	UUserWidget* uiInventoryWidget;
};
