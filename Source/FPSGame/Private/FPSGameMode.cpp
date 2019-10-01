// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn) 
	{
		//nullptr disables whatever was required in parameters
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpointClass) 
		{
			TArray<AActor*> ReturnedActors;
			TArray<AActor*> ReturnedBHoleLocs;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);
			UGameplayStatics::GetAllActorsOfClass(this, BlackHoleLocation, ReturnedBHoleLocs);

			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];


				APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());

				if (PlayerController)
				{
					PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.2f, EViewTargetBlendFunction::VTBlend_Cubic);

					if (ReturnedBHoleLocs.Num() > 0) 
					{
						AActor* NewBlackHoleLocation = ReturnedBHoleLocs[0];
						FVector SpawnLocation = NewBlackHoleLocation->GetActorLocation();
						FActorSpawnParameters ActorSpawnParams;
						ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

						/*ActorSpawnParams.Name = "BlackWhole";*/
					//	GetWorld()->SpawnActor(BlackHoleBlueprint, SpawnLocation, FVector(0));
					//	UE_LOG(LogTemp, Log, TEXT("SPAWWWWWN"));
						//AActor* temp = GetWorld()->SpawnActor(BlackHoleBlueprint/*, SpawnLocation, FRotator(0), ActorSpawnParams*/);
						//FString stringName = temp->GetName();
						//UE_LOG(LogTemp, Log, TEXT("Name: %s"), *stringName);
					}
					//spawn blueprint
				}
			}
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr, please update GameMode class with valid subclass, Cannot change spectating view targets"));
		}
	}

	OnMissionCompleted(InstigatorPawn);


}
