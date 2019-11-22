// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "MusicManager.generated.h"

class UAudioComponent;

UENUM(BlueprintType)
enum class TrackStage : uint8
{
	TS_Track1, 
	TS_Track2,
	TS_Track3
};

UENUM(BlueprintType)
enum class TrackIntensity : uint8
{
	TS_Intensity1,
	TS_Intensity2,
	TS_Intensity3
};

UENUM(BlueprintType)
enum class TrackLayerSelection : uint8
{
	T1L1,
	T1L2,
	T1L3,
	T1L4,
	T1L5,
	T1L6,
	T1L7,
	T1L8,

	T2L1,
	T2L2,

	T3L1
};

UCLASS()
class FPSGAME_API AMusicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicManager();

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TrackStage TrackStageState;

	/*** TRACKS STAGE 1 ***/
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer1;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer2;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer3;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer4;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer5;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer6;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer7;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T1AudioCompLayer8;

	/*** TRACKS STAGE 2 ***/
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T2AudioCompLayer1;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T2AudioCompLayer2;

	/*** TRACKS STAGE 3 ***/
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* T3AudioCompLayer1;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MaxVolume = 0.7f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MinVolume = 0.0003f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MinVolumeCheck = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float InterpSpeedIn = 0.12f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float InterpSpeedOut = 1.1f;

	UPROPERTY()
	float T1Layer1Vol;
	UPROPERTY()
	float T1Layer2Vol;
	UPROPERTY()
	float T1Layer3Vol;
	UPROPERTY()
	float T1Layer4Vol;
	UPROPERTY()
	float T1Layer5Vol;
	UPROPERTY()
	float T1Layer6Vol;
	UPROPERTY()
	float T1Layer7Vol;
	UPROPERTY()
	float T1Layer8Vol;

	UPROPERTY()
	float T2Layer1Vol;
	UPROPERTY()
	float T2Layer2Vol;

	UPROPERTY()
	float T3Layer1Vol;

	UPROPERTY()
	bool T1bLayer1 = false;
	UPROPERTY()
	bool T1bLayer2 = false;
	UPROPERTY()
	bool T1bLayer3 = false;
	UPROPERTY()
	bool T1bLayer4 = false;
	UPROPERTY()
	bool T1bLayer5 = false;
	UPROPERTY()
	bool T1bLayer6 = false;
	UPROPERTY()
	bool T1bLayer7 = false;
	UPROPERTY()
	bool T1bLayer8 = false;

	UPROPERTY()
	bool T2bLayer1 = false;
	UPROPERTY()
	bool T2bLayer2 = false;

	UPROPERTY()
	bool T3bLayer1 = false;

	UFUNCTION()
	void FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void InitializePlay();

	UFUNCTION()
	void ChangeTrackStage(TrackStage NewStage, TrackIntensity TrackIntensityState);

	UFUNCTION()
	void StopLayerOnMinVolCheck();

	UFUNCTION()
	void FadeLayer(bool bCheck, TrackLayerSelection SelectedTrack);

	UFUNCTION()
	void VolumeUpdater(float DeltaTime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
