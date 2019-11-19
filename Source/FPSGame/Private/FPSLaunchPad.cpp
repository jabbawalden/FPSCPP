// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxTrigger->SetupAttachment(MeshComp);

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OverlapLaunchPad);
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

void AFPSLaunchPad::LaunchCube(AActor* MyActor)
{
	if (MyActor) 
	{
		LaunchDirection = AFPSLaunchPad::GetActorForwardVector();

		//set up force (between 0 and 1)
		LaunchDirection.Z = UpForce;

		bCanLaunch = false;
		UPrimitiveComponent* MyComponent = Cast<UPrimitiveComponent>(MyActor->GetRootComponent());

		if(MyComponent) 
		{
			if (MyComponent->GetGenerateOverlapEvents())
			{ 

				MyComponent->AddImpulse(LaunchDirection * ImpulseForce);
			}
		}
		//MyActor->UPrimitiveComponent::AddImpulse(LaunchDirection * LaunchForce);
	}
}

void AFPSLaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OverlappedComponent)
	{
		//UE_LOG(LogTemp, Log, TEXT("Component is overlapping"));
	}
}

void AFPSLaunchPad::NotifyActorBeginOverlap(AActor* MyActor)
{
	Super::NotifyActorBeginOverlap(MyActor);
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(MyActor);

	if (MyCharacter)
	{
		AFPSLaunchPad::LaunchPlayer(MyCharacter);
	}
	else if (MyActor)
	{
		AFPSLaunchPad::LaunchCube(MyActor);
		//UE_LOG(LogTemp, Log, TEXT("Actor found"));
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
	else if (MyActor->bGenerateOverlapEventsDuringLevelStreaming)
	{
		bCanLaunch = true;
		bIsCharacter = false;
	}
}

