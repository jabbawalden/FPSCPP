// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

class UGameplayStatics;

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpawnLocations;

	UPROPERTY(EditDefaultsOnly, Category = "BlackHole")
	TSubclassOf<AActor> BlackHoleBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Value")
	float WaitTime = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Value")
	float NewTime = 0.f;

	bool bCanSpawn = false;

	bool bGameOver = false;

	UFUNCTION()
	void SpawnBlackHole();

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

	virtual void Tick(float DeltaSecond) override;
};



