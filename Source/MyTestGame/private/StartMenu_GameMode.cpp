// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "HUD_StartMenu.h"
#include "Controller_StartMenu.h"

AStartMenu_GameMode::AStartMenu_GameMode() {
	HUDClass = AHUD_StartMenu::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AController_StartMenu::StaticClass();
}