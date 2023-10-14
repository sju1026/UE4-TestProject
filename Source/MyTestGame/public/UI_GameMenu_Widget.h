// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"

#include "UI_GameMenu_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API UUI_GameMenu_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GameMenu_Close = nullptr;

	UFUNCTION()
		void Btn_GameMenu_CloseWindow();
};
