// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_InGame.h"
#include "BasicCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "MyTestGameGameModeBase.h"
#include "MyTestGameCharacter.h"

AController_InGame::AController_InGame()
{
	isShowGameMenu = false;
	isShowInventory = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UPB_GamePlay.UPB_GamePlay_C'"));
	if (obj.Succeeded())
	{
		uiGameBPClass = obj.Class;
	}

	if (uiGameBPClass)
	{
		uiGameWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameBPClass);
		if (uiGameWidget)
		{
			uiGameWidget->AddToViewport();
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> gamemenuUI(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UBP_Menu.UBP_Menu_C'"));
	if (gamemenuUI.Succeeded())
	{
		uiGameMenuBPClass = gamemenuUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DieUI(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UBP_Die.UBP_Die_C'"));
	if (DieUI.Succeeded())
	{
		uiGameDieBPClass = DieUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUI(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UBP_Inventory.UBP_Inventory_C'"));
	if (InventoryUI.Succeeded())
	{
		uiInventoryBPClass = InventoryUI.Class;
	}
}

void AController_InGame::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AController_InGame::ShowGameMenu);
	InputComponent->BindAction("CloseGameMenu", IE_Pressed, this, &AController_InGame::CloseGameMenu);
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AController_InGame::ShowInventory);
	InputComponent->BindAction("ViewMousePointer", IE_Pressed, this, &AController_InGame::ViewMousePointer);
	InputComponent->BindAction("ViewMousePointer", IE_Released, this, &AController_InGame::ViewMousePointer_Exit);
}

void AController_InGame::ShowGameMenu()
{
	if (uiGameMenuBPClass && isShowGameMenu == false)
	{
		uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);
		if (uiGameMenuWidget)
		{
			uiGameMenuWidget->AddToViewport();
		}
		isShowGameMenu = true;

		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
	}
}

void AController_InGame::CloseGameMenu()
{
	if (isShowGameMenu)
	{
		uiGameMenuWidget->RemoveFromViewport();
		isShowGameMenu = false;

		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;
	}
}

void AController_InGame::ShowDieUI()
{
	if (uiGameDieBPClass)
	{
		uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameDieBPClass);
		if (uiGameDieWidget)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Die");
			uiGameWidget->RemoveFromParent();
			uiGameDieWidget->AddToViewport();

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
		}
	}
}

void AController_InGame::ShowInventory()
{
	if (uiInventoryBPClass && isShowInventory == false)
	{
		AMyTestGameCharacter* MyPlayerCharacter = Cast<AMyTestGameCharacter>(GetOwner());

		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);
		if (uiInventoryWidget)
		{
			uiInventoryWidget->AddToViewport();
			//CreateItemSlots();

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
		}
		isShowInventory = true;
	}
}

void AController_InGame::ViewMousePointer()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AController_InGame::ViewMousePointer_Exit()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}

void AController_InGame::CloseInventory()
{
	if (isShowInventory)
	{
		uiInventoryWidget->RemoveFromViewport();
		isShowInventory = false;

		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;
	}

}

/*void AController_InGame::CreateItemSlots()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;


	//Show ItemSlots
	//UUI_Inventory_Widget* MyInvenWidgetClass = Cast<UUI_Inventory_Widget>(GetWorld());
	//
	//UUI_Inventory_Widget* MyInvenPanel = Cast<UUI_Inventory_Widget>(GetWorld());
	//auto s = MyInvenPanel->GridPanel_ItemSlots;
	//
	//for (int i = 0; i < 8; i++)
	//{
	//	//MyInvenWidgetClass->GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	s->AddChildToGrid(uiItemSlotWidget);
	//	//uiItemSlotWidget->AddToViewport();
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, __FUNCTION__);
	//}
}
*/