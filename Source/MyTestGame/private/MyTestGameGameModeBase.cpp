// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyTestGameGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HUD_GameHUD.h"
#include "MyTestGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Controller_InGame.h"

AMyTestGameGameModeBase::AMyTestGameGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> player(TEXT("Blueprint'/Game/_My/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}
	HUDClass = AHUD_GameHUD::StaticClass();
	PlayerControllerClass = AController_InGame::StaticClass();
}

void AMyTestGameGameModeBase::BeginPlay() {
	Super::BeginPlay();
	AMyTestGameCharacter* MyTestGameCharacter = Cast<AMyTestGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//int temp = MyPlayerCharacter->getNextLevel();
}



void AMyTestGameGameModeBase::ChangeUI()
{
	currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	currentWidget->AddToViewport();
}
