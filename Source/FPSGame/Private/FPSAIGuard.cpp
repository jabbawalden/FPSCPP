// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Comp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeePlayer);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearPlayer);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSAIGuard::OnSeePlayer(APawn* SeenPlayer)
{
	if (SeenPlayer == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPlayer->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AFPSAIGuard::OnHearPlayer(APawn* HeardPlayer, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), HeardPlayer->GetActorLocation(), 32.0f, 12, FColor::Blue, false, 10.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

