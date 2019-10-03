// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UCapsuleComponent;
class UPrimitiveComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	float LaunchForce = 12000;

	UPROPERTY(EditAnywhere, Category = "Components")
	float ImpulseForce = 1225000;

	UPROPERTY(EditAnywhere, Category = "Components")
	float UpForce = 0.8f;

	UFUNCTION()
	void LaunchPlayer(AFPSCharacter* MyCharacter);

	UFUNCTION()
	void LaunchCube(AActor* MyComponent);

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bIsCharacter = false;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bCanLaunch = true;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	FVector LaunchDirection;

	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	virtual void NotifyActorBeginOverlap(AActor* MyActor) override;

	virtual void NotifyActorEndOverlap(AActor* MyActor) override;
};
