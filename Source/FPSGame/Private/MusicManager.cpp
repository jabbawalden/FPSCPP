// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "MusicManager.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioCompLayer1->SetupAttachment(SceneComp);
	AudioCompLayer1->VolumeMultiplier = MinVolume;
	Layer1Vol = MinVolume;
	AudioCompLayer1->bAutoActivate = false;

	AudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp2"));
	AudioCompLayer2->SetupAttachment(SceneComp);
	AudioCompLayer2->VolumeMultiplier = MinVolume;
	Layer2Vol = MinVolume;
	AudioCompLayer2->bAutoActivate = false;

	AudioCompLayer3 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp3"));
	AudioCompLayer3->SetupAttachment(SceneComp);
	AudioCompLayer3->VolumeMultiplier = MinVolume;
	Layer3Vol = MinVolume;
	AudioCompLayer3->bAutoActivate = false;

	bLayer1 = false;
	bLayer2 = false;
	bLayer3 = false;
}

void AMusicManager::FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MaxVolume, DeltaTime, InterpSpeed);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AMusicManager::FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MinVolume, DeltaTime, InterpSpeed);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AMusicManager::FadeLayer1(bool bCheck)
{
	bLayer1 = bCheck;
	UE_LOG(LogTemp, Log, TEXT("Fading l"));
}

void AMusicManager::FadeLayer2(bool bCheck)
{
	bLayer2 = bCheck;
	UE_LOG(LogTemp, Log, TEXT("Fading 2"));
}

void AMusicManager::FadeLayer3(bool bCheck)
{
	bLayer3 = bCheck;
	UE_LOG(LogTemp, Log, TEXT("Fading 3"));
}

void AMusicManager::VolumeUpdater(float DeltaTime)
{
	if (bLayer1)
		AMusicManager::FadeInAudioLayer(AudioCompLayer1, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer1, DeltaTime);

	if (bLayer2)
		AMusicManager::FadeInAudioLayer(AudioCompLayer2, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer2, DeltaTime);

	if (bLayer3)
		AMusicManager::FadeInAudioLayer(AudioCompLayer3, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer3, DeltaTime);
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	AudioCompLayer1->Play();
	AudioCompLayer2->Play();
	AudioCompLayer3->Play();
}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AMusicManager::VolumeUpdater(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Volume value = %f"), AudioCompLayer1->VolumeMultiplier);
}

