// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSStorm.h"

// Sets default values
AFPSStorm::AFPSStorm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSStorm::OnBeginComponentOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComp->SetupAttachment(SphereComp);
}

void AFPSStorm::MoveStorm(float DeltaTime)
{
	FVector Direction = LocsArray[TargetIndex]->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	FVector NextLoc = GetActorLocation() + Direction * MovementSpeed * DeltaTime;
	SetActorLocation(NextLoc);
	//UE_LOG(LogTemp, Log, TEXT("Next location is = %s"), NextLoc);
}


void AFPSStorm::ReturnIndex()
{
	if (LocsArray.Num() == 0)
		return;

	CurrentDistance = FVector::Distance(GetActorLocation(), LocsArray[TargetIndex]->GetActorLocation());

	if (CurrentDistance <= MinDistance)
	{
		if (TargetIndex < LocsArray.Num() - 1)
			TargetIndex++;
		else
			TargetIndex = 0;
	}
}

void AFPSStorm::OnBeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("WE OVERLAPPED WITH SOMETHING %s"), *OtherActor->GetFName().ToString());

	//UFPSStormComponent* StormComp = Cast<UFPSStormComponent>(OtherComp);
	//TSubclassOf<AFPSCharacter> CharacterClass;
	AFPSCharacter* CharRef = Cast<AFPSCharacter>(OtherActor);

	if (CharRef != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("WE FOUND OUR CHARACTER"));
	}

	TArray<UFPSStormComponent*> StormCompArray;

	TSubclassOf<UFPSStormComponent> StormCompClass;
	UFPSStormComponent* StormComp = Cast<UFPSStormComponent>(OtherActor->GetComponentByClass(StormCompClass));
	//OtherActor->GetComponents<UActorComponent>(StormCompClass)

	//UFPSStormComponent* StormComp;
	//OtherActor->GetComponents<UFPSStormComponent>();

	if (StormComp != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("STORM FOUND A STORM COMP"));
		StormComp->StormEvent.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NO STORM COMP WAS FOUND"));
	}
}

// Called when the game starts or when spawned
void AFPSStorm::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPSStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFPSStorm::ReturnIndex();
	AFPSStorm::MoveStorm(DeltaTime);
}

