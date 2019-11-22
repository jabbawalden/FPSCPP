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

	AudioCompLayer4 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp4"));
	AudioCompLayer4->SetupAttachment(SceneComp);
	AudioCompLayer4->VolumeMultiplier = MinVolume;
	Layer4Vol = MinVolume;
	AudioCompLayer4->bAutoActivate = false;

	AudioCompLayer5 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp5"));
	AudioCompLayer5->SetupAttachment(SceneComp);
	AudioCompLayer5->VolumeMultiplier = MinVolume;
	Layer5Vol = MinVolume;
	AudioCompLayer5->bAutoActivate = false;

	AudioCompLayer6 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp6"));
	AudioCompLayer6->SetupAttachment(SceneComp);
	AudioCompLayer6->VolumeMultiplier = MinVolume;
	Layer6Vol = MinVolume;
	AudioCompLayer6->bAutoActivate = false;

	AudioCompLayer7 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp7"));
	AudioCompLayer7->SetupAttachment(SceneComp);
	AudioCompLayer7->VolumeMultiplier = MinVolume;
	Layer7Vol = MinVolume;
	AudioCompLayer7->bAutoActivate = false;

	AudioCompLayer8 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp8"));
	AudioCompLayer8->SetupAttachment(SceneComp);
	AudioCompLayer8->VolumeMultiplier = MinVolume;
	Layer8Vol = MinVolume;
	AudioCompLayer8->bAutoActivate = false;

	bLayer1 = false;
	bLayer2 = false;
	bLayer3 = false;
	bLayer4 = false;
	bLayer5 = false;
	bLayer6 = false;
	bLayer7 = false;
	bLayer8 = false;
}

void AMusicManager::FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MaxVolume, DeltaTime, InterpSpeedIn);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AMusicManager::FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MinVolume, DeltaTime, InterpSpeedOut);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AMusicManager::FadeLayer(bool bCheck, int Index)
{
	switch (Index)
	{
		case 1:
			bLayer1 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 2:
			bLayer2 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 3:
			bLayer3 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 4:
			bLayer4 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 5:
			bLayer5 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 6:
			bLayer6 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 7:
			bLayer7 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;

		case 8:
			bLayer8 = bCheck;
			UE_LOG(LogTemp, Log, TEXT("Fading l"));
			break;
	}
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

	if (bLayer4)
		AMusicManager::FadeInAudioLayer(AudioCompLayer4, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer4, DeltaTime);

	if (bLayer5)
		AMusicManager::FadeInAudioLayer(AudioCompLayer5, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer5, DeltaTime);

	if (bLayer6)
		AMusicManager::FadeInAudioLayer(AudioCompLayer6, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer6, DeltaTime);

	if (bLayer7)
		AMusicManager::FadeInAudioLayer(AudioCompLayer7, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer7, DeltaTime);

	if (bLayer8)
		AMusicManager::FadeInAudioLayer(AudioCompLayer8, DeltaTime);
	else
		AMusicManager::FadeOutAudioLayer(AudioCompLayer8, DeltaTime);
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();

	AudioCompLayer1->Play();
	AudioCompLayer2->Play();
	AudioCompLayer3->Play();
	AudioCompLayer4->Play();
	AudioCompLayer5->Play();
	AudioCompLayer6->Play();
	AudioCompLayer7->Play();
	AudioCompLayer8->Play();

}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AMusicManager::VolumeUpdater(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Volume value = %f"), AudioCompLayer1->VolumeMultiplier);
}

