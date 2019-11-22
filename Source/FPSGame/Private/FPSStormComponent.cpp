// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSStormComponent.h"

// Sets default values for this component's properties
UFPSStormComponent::UFPSStormComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFPSStormComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("BEGIN PLAY IN STORM COMP PLAYED"));
	// ...
}


// Called every frame
void UFPSStormComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


