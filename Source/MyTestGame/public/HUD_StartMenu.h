// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AHUD_StartMenu : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_StartMenu();
	void BeginPlay()override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
