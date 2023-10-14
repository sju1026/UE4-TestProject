// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"

#include "UI_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API UUI_GameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GameMenu = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory = nullptr;

private:
	UFUNCTION()
		void Btn_GameMenu_Clicked();

	UFUNCTION()
		void Btn_Inventory_Clicked();

};