// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "MusicManager.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	/*** TRACKS STAGE 1 ***/
	T1AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp"));
	T1AudioCompLayer1->SetupAttachment(SceneComp);
	T1AudioCompLayer1->VolumeMultiplier = MinVolume;
	T1Layer1Vol = MinVolume;
	T1AudioCompLayer1->bAutoActivate = false;

	T1AudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp2"));
	T1AudioCompLayer2->SetupAttachment(SceneComp);
	T1AudioCompLayer2->VolumeMultiplier = MinVolume;
	T1Layer2Vol = MinVolume;
	T1AudioCompLayer2->bAutoActivate = false;

	T1AudioCompLayer3 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp3"));
	T1AudioCompLayer3->SetupAttachment(SceneComp);
	T1AudioCompLayer3->VolumeMultiplier = MinVolume;
	T1Layer3Vol = MinVolume;
	T1AudioCompLayer3->bAutoActivate = false;

	T1AudioCompLayer4 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp4"));
	T1AudioCompLayer4->SetupAttachment(SceneComp);
	T1AudioCompLayer4->VolumeMultiplier = MinVolume;
	T1Layer4Vol = MinVolume;
	T1AudioCompLayer4->bAutoActivate = false;

	T1AudioCompLayer5 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp5"));
	T1AudioCompLayer5->SetupAttachment(SceneComp);
	T1AudioCompLayer5->VolumeMultiplier = MinVolume;
	T1Layer5Vol = MinVolume;
	T1AudioCompLayer5->bAutoActivate = false;

	T1AudioCompLayer6 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp6"));
	T1AudioCompLayer6->SetupAttachment(SceneComp);
	T1AudioCompLayer6->VolumeMultiplier = MinVolume;
	T1Layer6Vol = MinVolume;
	T1AudioCompLayer6->bAutoActivate = false;

	T1AudioCompLayer7 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp7"));
	T1AudioCompLayer7->SetupAttachment(SceneComp);
	T1AudioCompLayer7->VolumeMultiplier = MinVolume;
	T1Layer7Vol = MinVolume;
	T1AudioCompLayer7->bAutoActivate = false;

	T1AudioCompLayer8 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp8"));
	T1AudioCompLayer8->SetupAttachment(SceneComp);
	T1AudioCompLayer8->VolumeMultiplier = MinVolume;
	T1Layer8Vol = MinVolume;
	T1AudioCompLayer8->bAutoActivate = false;

	/*** TRACKS STAGE 2 ***/
	T2AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T2AudioComp1"));
	T2AudioCompLayer1->SetupAttachment(SceneComp);
	T2AudioCompLayer1->VolumeMultiplier = MinVolume;
	T2Layer1Vol = MinVolume;
	T2AudioCompLayer1->bAutoActivate = false;

	T2AudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("T2AudioComp2"));
	T2AudioCompLayer2->SetupAttachment(SceneComp);
	T2AudioCompLayer2->VolumeMultiplier = MinVolume;
	T2Layer2Vol = MinVolume;
	T2AudioCompLayer2->bAutoActivate = false;

	/*** TRACKS STAGE 3 ***/
	T3AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T3AudioComp1"));
	T3AudioCompLayer1->SetupAttachment(SceneComp);
	T3AudioCompLayer1->VolumeMultiplier = MinVolume;
	T3Layer1Vol = MinVolume;
	T3AudioCompLayer1->bAutoActivate = false;
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

void AMusicManager::InitializePlay()
{
	switch (TrackStageState)
	{
		case TrackStage::TS_Track1:
			T1AudioCompLayer1->Play();
			T1AudioCompLayer2->Play();
			T1AudioCompLayer3->Play();
			T1AudioCompLayer4->Play();
			T1AudioCompLayer5->Play();
			T1AudioCompLayer6->Play();
			T1AudioCompLayer7->Play();
			T1AudioCompLayer8->Play();
			break;

		case TrackStage::TS_Track2:
			T2AudioCompLayer1->Play();
			T2AudioCompLayer2->Play();
			break;

		case TrackStage::TS_Track3:
			T3AudioCompLayer1->Play();
			break;
	}
}

void AMusicManager::ChangeTrackStage(TrackStage NewStage, TrackIntensity TrackIntensityState)
{
	TrackStageState = NewStage;

	//based on track change stage, change layer bools to fade in

	switch (NewStage)
	{
		case TrackStage::TS_Track1:

			//set other booleans to false so they fade out
			T2bLayer1 = false;
			T2bLayer2 = false;

			T3bLayer1 = false;

			//based on track intensity, set certain layers to true when track stage is initiated
			switch (TrackIntensityState)
			{
			case TrackIntensity::TS_Intensity1:
				T1bLayer1 = true;
				break;

			case TrackIntensity::TS_Intensity2:
				T1bLayer2 = true;
				T1bLayer3 = true;
				T1bLayer4 = true;
				break;

			case TrackIntensity::TS_Intensity3:
				T1bLayer5 = true;
				T1bLayer6 = true;
				T1bLayer7 = true;
				T1bLayer8 = true;
				break;
			}

			T1AudioCompLayer1->Play();
			T1AudioCompLayer2->Play();
			T1AudioCompLayer3->Play();
			T1AudioCompLayer4->Play();
			T1AudioCompLayer5->Play();
			T1AudioCompLayer6->Play();
			T1AudioCompLayer7->Play();
			T1AudioCompLayer8->Play();

			break;

		case TrackStage::TS_Track2:

			//set other booleans to false so they fade out
			T1bLayer1 = false;
			T1bLayer2 = false;
			T1bLayer3 = false;
			T1bLayer4 = false;
			T1bLayer5 = false;
			T1bLayer6 = false;
			T1bLayer7 = false;
			T1bLayer8 = false;

			T3bLayer1 = false;

			//based on track intensity, set certain layers to true when track stage is initiated
			switch (TrackIntensityState)
			{
			case TrackIntensity::TS_Intensity1:
				T2bLayer1 = true;
				break;

			case TrackIntensity::TS_Intensity2:
				T2bLayer1 = true;
				T2bLayer2 = true;
				break;

			case TrackIntensity::TS_Intensity3:
				T2bLayer1 = true;
				T2bLayer2 = true;
				break;
			}

			T2AudioCompLayer1->Play();
			T2AudioCompLayer2->Play();

			break;

		case TrackStage::TS_Track3:

			//set other booleans to false so they fade out
			T1bLayer1 = false;
			T1bLayer2 = false;
			T1bLayer3 = false;
			T1bLayer4 = false;
			T1bLayer5 = false;
			T1bLayer6 = false;
			T1bLayer7 = false;
			T1bLayer8 = false;

			T2bLayer1 = false;
			T2bLayer2 = false;

			//no track stages required as of yet
			T3bLayer1 = true;

			T3AudioCompLayer1->Play();

			break;
	}
}

void AMusicManager::FadeLayer(bool bCheck, TrackLayerSelection SelectedTrack)
{
	switch (SelectedTrack)
	{
		case TrackLayerSelection::T1L1:
			T1bLayer1 = bCheck;
			break;
		case TrackLayerSelection::T1L2:
			T1bLayer2 = bCheck;
			break;
		case TrackLayerSelection::T1L3:
			T1bLayer3 = bCheck;
			break;
		case TrackLayerSelection::T1L4:
			T1bLayer4 = bCheck;
			break;
		case TrackLayerSelection::T1L5:
			T1bLayer5 = bCheck;
			break;
		case TrackLayerSelection::T1L6:
			T1bLayer6 = bCheck;
			break;
		case TrackLayerSelection::T1L7:
			T1bLayer7 = bCheck;
			break;
		case TrackLayerSelection::T1L8:
			T1bLayer8 = bCheck;
			break;

		case TrackLayerSelection::T2L1:
			T2bLayer1 = bCheck;
			break;
		case TrackLayerSelection::T2L2:
			T2bLayer2 = bCheck;
			break;

		case TrackLayerSelection::T3L1:
			T3bLayer1 = bCheck;
			break;
	}
}

void AMusicManager::VolumeUpdater(float DeltaTime)
{
	//Controls layer fades based on bool
	//if in appropriate track stage, then fades in, otherwise does not -> placed as a security measure

	if (TrackStageState == TrackStage::TS_Track1)
	{
		if (T1bLayer1)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer1, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer1, DeltaTime);

		if (T1bLayer2)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer2, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer2, DeltaTime);

		if (T1bLayer3)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer3, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer3, DeltaTime);

		if (T1bLayer4)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer4, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer4, DeltaTime);

		if (T1bLayer5)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer5, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer5, DeltaTime);

		if (T1bLayer6)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer6, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer6, DeltaTime);

		if (T1bLayer7)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer7, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer7, DeltaTime);

		if (T1bLayer8)
			AMusicManager::FadeInAudioLayer(T1AudioCompLayer8, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T1AudioCompLayer8, DeltaTime);
	}
	else
	{
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer1, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer2, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer3, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer4, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer5, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer6, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer7, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T1AudioCompLayer8, DeltaTime);
	}



	if (TrackStageState == TrackStage::TS_Track2)
	{
		if (T2bLayer1)
			AMusicManager::FadeInAudioLayer(T2AudioCompLayer1, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T2AudioCompLayer1, DeltaTime);

		if (T2bLayer2)
			AMusicManager::FadeInAudioLayer(T2AudioCompLayer2, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T2AudioCompLayer2, DeltaTime);
	}
	else
	{
		AMusicManager::FadeOutAudioLayer(T2AudioCompLayer1, DeltaTime);
		AMusicManager::FadeOutAudioLayer(T2AudioCompLayer2, DeltaTime);
	}


	if (TrackStageState == TrackStage::TS_Track2)
	{
		if (T3bLayer1)
			AMusicManager::FadeInAudioLayer(T3AudioCompLayer1, DeltaTime);
		else
			AMusicManager::FadeOutAudioLayer(T3AudioCompLayer1, DeltaTime);
	}
	else
	{
		AMusicManager::FadeOutAudioLayer(T3AudioCompLayer1, DeltaTime);
	}

}

void AMusicManager::StopLayerOnMinVolCheck()
{
	//sets layers to stop based on track stage selected

	switch (TrackStageState)
	{

	case TrackStage::TS_Track1:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T2AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer1->Stop();
		if (T2AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer2->Stop();

		if (T3AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T3AudioCompLayer1->Stop();
		break;

	case TrackStage::TS_Track2:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T1AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer1->Stop();
		if (T1AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer2->Stop();
		if (T1AudioCompLayer3->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer3->Stop();
		if (T1AudioCompLayer4->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer4->Stop();
		if (T1AudioCompLayer5->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer5->Stop();
		if (T1AudioCompLayer6->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer6->Stop();
		if (T1AudioCompLayer7->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer7->Stop();
		if (T1AudioCompLayer8->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer8->Stop();

		if (T3AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T3AudioCompLayer1->Stop();
		break;

	case TrackStage::TS_Track3:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T1AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer1->Stop();
		if (T1AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer2->Stop();
		if (T1AudioCompLayer3->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer3->Stop();
		if (T1AudioCompLayer4->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer4->Stop();
		if (T1AudioCompLayer5->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer5->Stop();
		if (T1AudioCompLayer6->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer6->Stop();
		if (T1AudioCompLayer7->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer7->Stop();
		if (T1AudioCompLayer8->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer8->Stop();

		if (T2AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer1->Stop();
		if (T2AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer2->Stop();

		break;
	}

}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();

	TrackStageState = TrackStage::TS_Track1;
	T1bLayer1 = true;

	AMusicManager::InitializePlay();

}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//sets volume transitions based on booleans
	AMusicManager::VolumeUpdater(DeltaTime);
	//based on track stage, stops all other layers when volume is below a certain amount
	AMusicManager::StopLayerOnMinVolCheck();

	//UE_LOG(LogTemp, Log, TEXT("Volume value = %f"), AudioCompLayer1->VolumeMultiplier);
}

