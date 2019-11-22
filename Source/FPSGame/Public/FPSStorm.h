// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"
#include "FPSStormComponent.h"
#include "FPSStorm.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFPSStormComponent;
class AFPSCharacter;

UCLASS()
class FPSGAME_API AFPSStorm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSStorm();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Values")
	TArray<AActor*> LocsArray;

	UPROPERTY()
	float CurrentDistance;

	UPROPERTY(EditAnywhere, Category = "Values")
	float MinDistance = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Values")
	float MovementSpeed = 900.f;

	UPROPERTY(VisibleAnywhere, Category = "Values")
	int TargetIndex = 0;

	UFUNCTION()
	void MoveStorm(float DeltaTime);

	UFUNCTION()
	void ReturnIndex();
	
	UFUNCTION()
	void OnBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
