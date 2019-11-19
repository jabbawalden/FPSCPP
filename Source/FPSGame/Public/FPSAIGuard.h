// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class UKismetMathLibrary;
class ATargetPoint;

UENUM(BlueprintType)
enum class EAIState : uint8 
{
	idle,

	suspicious,

	alert
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<ATargetPoint*> PatrolPoints;

	//UKismetMathLibrary* MathFunctionLibrary;
	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	float DistanceCurrent;

	float DistanceThreshold = 70;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MovementSpeedMultiplier = 120;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	int32 PatrolIndex;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPlayer);

	UFUNCTION()
	void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	EAIState GuardState;

	UFUNCTION()
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI") 
	void OnStateChanged(EAIState NewState);

	UFUNCTION()
	void SetPatrolPoint();

	UFUNCTION()
	void MoveOnPatrol();

	UFUNCTION()
	void CheckDistance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
