// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UFPSAudioComponent::UFPSAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UDataTable> AudioDataEnemyObj(TEXT("DataTable'/Game/Blueprints/DT_AudioDataCharacter.DT_AudioDataEnemy'"));
	//static ConstructorHelpers::FObjectFinder<UDataTable> AudioDataPlayerObj(TEXT("DataTable'/Game/Blueprints/DT_AudioDataCharacter.DT_AudioDataPlayer'"));
	//static ConstructorHelpers::FObjectFinder<UDataTable> AudioDataEnvironmentObj(TEXT("DataTable'/Game/Blueprints/DT_AudioDataCharacter.DT_AudioDataEnvironment'"));
	////static ConstructorHelpers::FObjectFinder<UDataTable> AudioDataObject(TEXT("DataTable'/Game/Blueprints/DT_AudioDataCharacter.DT_AudioDataCharacter''"));

	//if (AudioDataEnemyObj.Succeeded())
	//	AudioDataEnemy = AudioDataEnemyObj.Object;

	//if (AudioDataPlayerObj.Succeeded())
	//	AudioDataPlayer = AudioDataPlayerObj.Object;

	//if (AudioDataEnvironmentObj.Succeeded())
	//	AudioDataEnvironment = AudioDataEnvironmentObj.Object;
	// ...
}

// Called when the game starts
void UFPSAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("BEGIN PLAY IN AUDIO COMP PLAYED"));
	// ...
}

// Called every frame
void UFPSAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFPSAudioComponent::PlaySound(FName CueType)
{
	//to call this function correctly, create variable of FAudioNames struct and initiate it
	//Pass a value from the struct into the CueType parameter

	if (AudioDataPlayer == nullptr)
		return;

	static const FString ContextString(TEXT("Audio Data Context"));
	FAudioData* OurAudioData = new FAudioData;

	switch (AudioObjType)
	{
		case AudioObjectType::ACT_Enemy:
			OurAudioData = AudioDataEnemy->FindRow<FAudioData>(CueType, ContextString, true);
			break;

		case AudioObjectType::ACT_Player:
			OurAudioData = AudioDataPlayer->FindRow<FAudioData>(CueType, ContextString, true);
			break;

		case AudioObjectType::ACT_Environment:
			OurAudioData = AudioDataEnvironment->FindRow<FAudioData>(CueType, ContextString, true);
			break;
	}

	if (AudioSpatialType == AudioSpatialSetting::ACT_2DSounds)
		UGameplayStatics::PlaySound2D(this, OurAudioData->SoundCue);
	if (AudioSpatialType == AudioSpatialSetting::ACT_3DSounds)
		UGameplayStatics::PlaySoundAtLocation(this, OurAudioData->SoundCue, GetOwner()->GetActorLocation());

	

	UE_LOG(LogTemp, Log, TEXT("WE PLAYED A SOUND"));
	//else play sound in 2D
}


