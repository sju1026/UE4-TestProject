// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "MyTestGameCharacter.h"
#include "UI_Inventory_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API UUI_Inventory_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory_Close = nullptr;

	UFUNCTION()
		void Btn_Inventory_CloseWindow();
};
