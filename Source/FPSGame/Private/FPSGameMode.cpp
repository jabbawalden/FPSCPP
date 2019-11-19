// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


AFPSGameMode::AFPSGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true; 

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)   
	{
		//nullptr disables whatever was required in parameters
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpointClass) 
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());

				if (PlayerController && !bGameOver)
				{
					PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.2f, EViewTargetBlendFunction::VTBlend_Cubic);
					bCanSpawn = true;	
					NewTime = UGameplayStatics::GetTimeSeconds(GetWorld()) + WaitTime;
				}
			}
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr, please update GameMode class with valid subclass, Cannot change spectating view targets"));
		}
	}

	if (!bGameOver) 
	{
		bGameOver = true;
		OnMissionCompleted(InstigatorPawn, bMissionSuccess);
	}

}

void AFPSGameMode::SpawnBlackHole()
{
	TArray<AActor*> ReturnedBHoleLocs;
	UGameplayStatics::GetAllActorsOfClass(this, SpawnLocations, ReturnedBHoleLocs);

	if (ReturnedBHoleLocs.Num() > 0)
	{
		//UE_LOG(LogTemp, Log, TEXT("Spawn Called"));
		AActor* NewBlackHoleLocation = ReturnedBHoleLocs[0];
		FVector NewSpawnLocation = NewBlackHoleLocation->GetActorLocation();
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor<AActor>(BlackHoleBlueprint, NewSpawnLocation, FRotator(0), ActorSpawnParams);
	}
}

void AFPSGameMode::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	float WorldTime = UGameplayStatics::GetTimeSeconds(GetWorld());

	if (bCanSpawn && NewTime <= WorldTime)
	{
		AFPSGameMode::SpawnBlackHole();
		bCanSpawn = false;
	}
}
