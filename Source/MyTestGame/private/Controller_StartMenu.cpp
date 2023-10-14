// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "BasicCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyTestGameGameModeBase.h"
#include "MyTestGameCharacter.h"

AController_StartMenu::AController_StartMenu()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}
