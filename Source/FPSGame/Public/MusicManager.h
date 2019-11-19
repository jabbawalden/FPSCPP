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

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MaxVolume = 0.7f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float MinVolume = 0.001f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
	float InterpSpeed = 2.1f;

	UPROPERTY()
	float Layer1Vol;

	UPROPERTY()
	float Layer2Vol;

	UPROPERTY()
	float Layer3Vol;

	UPROPERTY()
	bool bLayer1 = false;

	UPROPERTY()
	bool bLayer2 = false;

	UPROPERTY()
	bool bLayer3 = false;

	UFUNCTION()
	void FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime);

	UFUNCTION()
	void FadeLayer1(bool bCheck);

	UFUNCTION()
	void FadeLayer2(bool bCheck);

	UFUNCTION()
	void FadeLayer3(bool bCheck);

	UFUNCTION()
	void VolumeUpdater(float DeltaTime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
