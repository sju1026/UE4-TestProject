// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_StartMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AHUD_StartMenu::AHUD_StartMenu()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>ui(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UBP_StartMenu.UBP_StartMenu_C'"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}

void AHUD_StartMenu::BeginPlay()
{
	Super::BeginPlay();
	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}