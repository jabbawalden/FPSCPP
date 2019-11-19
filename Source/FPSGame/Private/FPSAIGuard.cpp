// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Rotator.h"
#include "FPSGameMode.h"
#include "FPSCharacter.h"
#include "Engine/TargetPoint.h"
#include "AIController.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Comp"));

	GuardState = EAIState::idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	//moved to begin play - did not work in constructor
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPlayer)
{
	if (SeenPlayer == nullptr)
	{
		return;
	}

	if (GuardState == EAIState::alert) 
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Player seen"));
	DrawDebugSphere(GetWorld(), SeenPlayer->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	
	if (GameMode)
	{
		GameMode->CompleteMission(SeenPlayer, false);
	}

	SetGuardState(EAIState::alert);
}

void AFPSAIGuard::OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::alert) 
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 10.0f);

	FVector MyLoc = GetActorLocation();
	FVector Direction = Location - MyLoc;
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3);

	SetGuardState(EAIState::suspicious);

}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::alert)
	{
		return;
	}

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState) 
	{
		return;
	}

	GuardState = NewState;

	OnStateChanged(GuardState);
}

void AFPSAIGuard::SetPatrolPoint()
{
	//set next index
	if (PatrolIndex >= PatrolPoints.Num() - 1) 
	{
		PatrolIndex = 0;
	}
	else 
	{
		PatrolIndex++;
	}

}

void AFPSAIGuard::MoveOnPatrol()
{
	//move character according to index and only if not in idle state
	if (GuardState == EAIState::idle) 
	{
		//MOVE

		FVector Direction = PatrolPoints[PatrolIndex]->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
		FVector NextLocation = GetActorLocation() += Direction * GetWorld()->GetDeltaSeconds() *  MovementSpeedMultiplier;
		//UE_LOG(LogTemp, Log, TEXT("Our movement vector speed is: %s"), *NextLocation.ToString());

		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0;
		NewLookAt.Roll = 0;

		SetActorLocation(NextLocation);
		SetActorRotation(NewLookAt);
	}
	else 
	{
		//No movement
	}
}

void AFPSAIGuard::CheckDistance()
{
	DistanceCurrent = FVector::Distance(GetActorLocation(), PatrolPoints[PatrolIndex]->GetActorLocation());
	//UE_LOG(LogTemp, Log, TEXT("Our distance is: %f"), DistanceCurrent);

	if (DistanceCurrent <= DistanceThreshold) 
	{
		SetPatrolPoint();
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PatrolPoints.Num() > 1) 
	{
		AFPSAIGuard::MoveOnPatrol();
		AFPSAIGuard::CheckDistance();
	}
	else 
	{

	}

}

