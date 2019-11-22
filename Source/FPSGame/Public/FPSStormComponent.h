// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSStormComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStormEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UFPSStormComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSStormComponent();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FStormEvent StormEvent; 

	UPROPERTY(EditAnywhere, Category = "Values")
	float TimerTest;

	UPROPERTY(EditAnywhere, Category = "Values")
	float StormTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
