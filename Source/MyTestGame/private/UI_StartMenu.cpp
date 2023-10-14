// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_StartMenu.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UUI_StartMenu::NativeConstruct()
{

	if (Btn_Start)
	{
		Btn_Start->OnClicked.AddDynamic(this, &UUI_StartMenu::Btn_StartGame_Clicked);
	}

	if (Btn_ExitGame)
	{
		Btn_ExitGame->OnClicked.AddDynamic(this, &UUI_StartMenu::Btn_ExitGame_Clicked);
	}
}


void UUI_StartMenu::Btn_StartGame_Clicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/_My/Maps/MainMap");
}

void UUI_StartMenu::Btn_ExitGame_Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}