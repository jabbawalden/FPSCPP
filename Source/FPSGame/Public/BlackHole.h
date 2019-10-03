// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class AFPSCharacter;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//outer sphere component to attract
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* AttractionSphereComp;

	////inner sphere component to destroy
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DestructiveSphereComp;

	//Black hole mesh
	UPROPERTY(EditDefaultsOnly, Category = "MeshMain")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float ForceStrength = -2000;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float AttractionRadius = 3000;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float DestructionRadius = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
