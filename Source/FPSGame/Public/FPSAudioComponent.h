// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "Engine/DataTable.h"
#include "FPSAudioComponent.generated.h"

class USoundCue;

UENUM(BlueprintType)
enum class AudioSpatialSetting : uint8
{
	ACT_3DSounds UMETA(DisplayName = "3DSounds"),
	ACT_2DSounds UMETA(DisplayName = "2DSounds")
};

UENUM(BlueprintType)
enum class AudioObjectType : uint8
{
	ACT_Enemy,
	ACT_Player,
	ACT_Environment
};

USTRUCT(BlueprintType)
struct FAudioNamesCharacter
{
	GENERATED_BODY()

	FName Walk = FName(TEXT("Walk"));
	FName Run = FName(TEXT("Run"));
	FName Transform = FName(TEXT("Transform"));
};

USTRUCT(BlueprintType)
struct FAudioNamesEnvironment
{
	GENERATED_BODY()

	FName Door = FName(TEXT("Door"));
	FName Electronic1 = FName(TEXT("Electronic1"));
	FName Water = FName(TEXT("Water"));
};

USTRUCT(BlueprintType)
struct FAudioData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* SoundCue;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UFPSAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSAudioComponent();

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	//AudioSpatialSetting AudioSpatialType;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioCompType", meta = (AllowPrivateAccess = "true"))
	//AudioObjectType AudioObjType;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//class UDataTable* AudioDataPlayer;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//class UDataTable* AudioDataEnemy;

	//private access means properties defined in C++ private scope will be accessible to blueprints
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	//class UDataTable* AudioDataEnvironment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	AudioSpatialSetting AudioSpatialType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AudioCompType")
	AudioObjectType AudioObjType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class UDataTable* AudioDataPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class UDataTable* AudioDataEnemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class UDataTable* AudioDataEnvironment;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	TArray<FName> RowNamesArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	USoundCue* SoundTest;

	UFUNCTION()
	void PlaySound(FName CueType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
