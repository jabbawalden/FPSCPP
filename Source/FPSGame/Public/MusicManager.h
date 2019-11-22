// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "MusicManager.generated.h"

class UAudioComponent;

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
	UAudioComponent* AudioCompLayer1;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer2;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer3;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer4;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer5;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer6;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer7;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioCompLayer8;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MaxVolume = 0.7f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MinVolume = 0.0003f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float InterpSpeedIn = 0.12f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float InterpSpeedOut = 1.1f;

	UPROPERTY()
	float Layer1Vol;

	UPROPERTY()
	float Layer2Vol;

	UPROPERTY()
	float Layer3Vol;

	UPROPERTY()
	float Layer4Vol;

	UPROPERTY()
	float Layer5Vol;

	UPROPERTY()
	float Layer6Vol;

	UPROPERTY()
	float Layer7Vol;

	UPROPERTY()
	float Layer8Vol;

	UPROPERTY()
	bool bLayer1 = false;

	UPROPERTY()
	bool bLayer2 = false;

	UPROPERTY()
	bool bLayer3 = false;

	UPROPERTY()
	bool bLayer4 = false;

	UPROPERTY()
	bool bLayer5 = false;

	UPROPERTY()
	bool bLayer6 = false;

	UPROPERTY()
	bool bLayer7 = false;

	UPROPERTY()
	bool bLayer8 = false;

	UFUNCTION()
	void FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void FadeLayer(bool bCheck, int Index);


	UFUNCTION()
	void VolumeUpdater(float DeltaTime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
