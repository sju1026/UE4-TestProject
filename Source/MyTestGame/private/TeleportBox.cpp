// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportBox.h"

ATeleportBox::ATeleportBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ATeleportBox::EnterTeleporter);
	OnActorEndOverlap.AddDynamic(this, &ATeleportBox::ExitTeleporter);

	teleporting = false;
}

void ATeleportBox::BeginPlay() {
	Super::BeginPlay();
}

void ATeleportBox::EnterTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTele)
		{
			AMyTestGameCharacter* character = Cast<AMyTestGameCharacter>(otherActor);
			if (character && !otherTele->teleporting)
			{
				teleporting = true;
				character->SetActorRotation(otherTele->GetActorRotation());
				character->GetController()->SetControlRotation(character->GetActorRotation());
				character->SetActorLocation(otherTele->GetActorLocation());
			}
		}
	}
}

void ATeleportBox::ExitTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTele && !teleporting)
		{
			otherTele->teleporting = false;
		}
	}
}
