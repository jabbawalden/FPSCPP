// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

//ensure cpp knows about these classes
class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;
class AFPSCharacter;

UCLASS()
class FPSGAME_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Particle Effects")
	UParticleSystem* PickUpEffects;

	void SpawnEffects();


public:	

	//specify override keyword as we are overiding implementation that is already avail
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
