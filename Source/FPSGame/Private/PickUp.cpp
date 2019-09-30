// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "FPSCharacter.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore); //ignore all
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); //channel and then overlap
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUp::SpawnEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpEffects, GetActorLocation());
}

void APickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if virtual function and overriding, call base class implementation 
	Super::NotifyActorBeginOverlap(OtherActor);

	SpawnEffects();
	MeshComp->ToggleVisibility(false);
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) 
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}

}

