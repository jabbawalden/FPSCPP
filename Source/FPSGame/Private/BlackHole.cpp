// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	DestructiveSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Comp"));

	DestructiveSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
	DestructiveSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestructiveSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	DestructiveSphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	DestructiveSphereComp->SetupAttachment(MeshComp);

	AttractionSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Comp"));
	AttractionSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttractionSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	AttractionSphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	AttractionSphereComp->SetupAttachment(MeshComp);
	AttractionSphereComp->SetSphereRadius(0, true);

	//DestructiveSphereComp->SetActive(false);
	//AttractionSphereComp->SetActive(false);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("BlackHole is here!"));

	AttractionSphereComp->SetSphereRadius(AttractionRadius, true);
	DestructiveSphereComp->SetSphereRadius(DestructionRadius, true);

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

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}
}

