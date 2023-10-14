// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"
#include "Controller_InGame.h"

void UUI_Inventory_Widget::NativeConstruct()
{

	if (Btn_Inventory_Close)
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
	}


	//SpawnSlots();
}

void UUI_Inventory_Widget::Btn_Inventory_CloseWindow()
{
	AController_InGame* contoller = Cast<AController_InGame>(GetOwningPlayer());
	contoller->CloseInventory();
}