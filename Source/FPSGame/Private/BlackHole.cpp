// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	DestructiveSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Comp"));
	//DestructiveSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//DestructiveSphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	DestructiveSphereComp->SetupAttachment(MeshComp);

	DestructiveSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	AttractionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Comp"));
	//AttractionSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore); 
	//AttractionSphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	AttractionSphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set TArray and add components to array from comps overlapping with attractionsphere
	TArray<UPrimitiveComponent*> OverlappingComps;
	AttractionSphereComp->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++) 
	{
		//set variable to current index
		UPrimitiveComponent* PrimComp = OverlappingComps[i];

		if (PrimComp && PrimComp->IsSimulatingPhysics()) 
		{
			const float SphereRadius = AttractionSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000; //negative to pull towards origin

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}
}

