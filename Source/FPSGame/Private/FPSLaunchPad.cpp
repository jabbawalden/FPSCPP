// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxTrigger->SetupAttachment(MeshComp);
}

void AFPSLaunchPad::LaunchPlayer(AFPSCharacter* MyCharacter)
{
	if (MyCharacter)
	{
		//get current launch pad forward vector
		LaunchDirection = AFPSLaunchPad::GetActorForwardVector();
		
		//set up force (between 0 and 1)
		LaunchDirection.Z = UpForce;

		//multiply launch direction by launch force
		MyCharacter->AFPSCharacter::LaunchCharacter(LaunchDirection * LaunchForce, false, false);
		bIsCharacter = true;
		bCanLaunch = false;
	}
}

void AFPSLaunchPad::NotifyActorBeginOverlap(AActor* MyActor)
{
	Super::NotifyActorBeginOverlap(MyActor);
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(MyActor);

	if (MyCharacter && bCanLaunch)
	{
		AFPSLaunchPad::LaunchPlayer(MyCharacter);
	}
}

void AFPSLaunchPad::NotifyActorEndOverlap(AActor* MyActor)
{
	Super::NotifyActorEndOverlap(MyActor);
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(MyActor);

	if (MyCharacter)
	{
		bCanLaunch = true;
		bIsCharacter = false;
	}
}

