// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameHUD.h"
#include "Controller_InGame.h"
#include "GameFramework/PlayerController.h"
#include "BasicCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UUI_GameHUD::NativeConstruct()
{
	if (Btn_GameMenu)
	{
		Btn_GameMenu->OnClicked.AddDynamic(this, &UUI_GameHUD::Btn_GameMenu_Clicked);
	}

	if (Btn_Inventory)
	{
		Btn_Inventory->OnClicked.AddDynamic(this, &UUI_GameHUD::Btn_Inventory_Clicked);
	}
}


void UUI_GameHUD::Btn_GameMenu_Clicked()
{
	AController_InGame* contoller = Cast<AController_InGame>(GetOwningPlayer());
	contoller->ShowGameMenu();
}


void UUI_GameHUD::Btn_Inventory_Clicked()
{
	AController_InGame* contoller = Cast<AController_InGame>(GetOwningPlayer());
	contoller->ShowInventory();
}