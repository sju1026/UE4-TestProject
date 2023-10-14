// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AHUD_GameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_GameHUD();
	void BeginPlay()override;
};
