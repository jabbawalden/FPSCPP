// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSAudioComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"


AFPSCharacter::AFPSCharacter()
{
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->RelativeRotation = FRotator(2.0f, -15.0f, 5.0f);
	Mesh1PComponent->RelativeLocation = FVector(0, 0, -160.0f);

	// Create a gun mesh component
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");

	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));

	StormComp = CreateDefaultSubobject<UFPSStormComponent>(TEXT("StormComp"));
	StormComp->StormEvent.AddDynamic(this, &AFPSCharacter::CharacterStormFunction);

	AudioComp = CreateDefaultSubobject<UFPSAudioComponent>(TEXT("AudioComp"));

	
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("FadeInLayer1", IE_Pressed, this, &AFPSCharacter::FadeLayer1);
	PlayerInputComponent->BindAction("FadeInLayer2", IE_Pressed, this, &AFPSCharacter::FadeLayer2);
	PlayerInputComponent->BindAction("FadeInLayer3", IE_Pressed, this, &AFPSCharacter::FadeLayer3);
	PlayerInputComponent->BindAction("FadeInLayer4", IE_Pressed, this, &AFPSCharacter::FadeLayer4);
	PlayerInputComponent->BindAction("FadeOutLayer1", IE_Pressed, this, &AFPSCharacter::FadeLayer5);
	PlayerInputComponent->BindAction("FadeOutLayer2", IE_Pressed, this, &AFPSCharacter::FadeLayer6);
	PlayerInputComponent->BindAction("FadeOutLayer3", IE_Pressed, this, &AFPSCharacter::FadeLayer7);
	PlayerInputComponent->BindAction("FadeOutLayer4", IE_Pressed, this, &AFPSCharacter::FadeLayer8);
}

void AFPSCharacter::FadeLayer1()
{
	if (MusicManagerRef == nullptr)
		return;

	OneIsOn = !OneIsOn;
	MusicManagerRef->FadeLayer(OneIsOn, TrackLayerSelection::T1L1);

	FAudioNamesCharacter* AudioNames = new FAudioNamesCharacter;
	AudioComp->PlaySound(AudioNames->Transform);
}


void AFPSCharacter::FadeLayer2()
{
	if (MusicManagerRef == nullptr)
		return;

	TwoIsOn = !TwoIsOn;
	MusicManagerRef->FadeLayer(TwoIsOn, TrackLayerSelection::T1L2);

	FAudioNamesCharacter* AudioNames = new FAudioNamesCharacter;
	AudioComp->PlaySound(AudioNames->Walk);
}


void AFPSCharacter::FadeLayer3()
{
	if (MusicManagerRef == nullptr)
		return;

	ThreeIsOn = !ThreeIsOn;
	MusicManagerRef->FadeLayer(ThreeIsOn, TrackLayerSelection::T1L3);
	MusicManagerRef->FadeLayer(ThreeIsOn, TrackLayerSelection::T1L4);
	MusicManagerRef->FadeLayer(ThreeIsOn, TrackLayerSelection::T1L5);

	FAudioNamesCharacter* AudioNames = new FAudioNamesCharacter;
	AudioComp->PlaySound(AudioNames->Run);
}

void AFPSCharacter::FadeLayer4()
{
	if (MusicManagerRef == nullptr)
		return;

	FourIsOn = !FourIsOn;
	MusicManagerRef->FadeLayer(FourIsOn, TrackLayerSelection::T1L6);
	MusicManagerRef->FadeLayer(FourIsOn, TrackLayerSelection::T1L7);
	MusicManagerRef->FadeLayer(FourIsOn, TrackLayerSelection::T1L8);

}

void AFPSCharacter::FadeLayer5()
{
	if (MusicManagerRef == nullptr)
		return;

	FiveIsOn = !FiveIsOn;
	MusicManagerRef->ChangeTrackStage(TrackStage::TS_Track2, TrackIntensity::TS_Intensity1);

}


void AFPSCharacter::FadeLayer6()
{
	if (MusicManagerRef == nullptr)
		return;

	SixIsOn = !SixIsOn;
	MusicManagerRef->FadeLayer(FourIsOn, TrackLayerSelection::T2L2);
}


void AFPSCharacter::FadeLayer7()
{
	if (MusicManagerRef == nullptr)
		return;

	SevenIsOn = !SevenIsOn;
	MusicManagerRef->ChangeTrackStage(TrackStage::TS_Track3, TrackIntensity::TS_Intensity1);

}

void AFPSCharacter::FadeLayer8()
{
	if (MusicManagerRef == nullptr)
		return;

	EightIsOn = !EightIsOn;
	MusicManagerRef->ChangeTrackStage(TrackStage::TS_Track1, TrackIntensity::TS_Intensity2);
}


void AFPSCharacter::CharacterStormFunction()
{
	UE_LOG(LogTemp, Log, TEXT("Storm event called on PLAYER character"));
}

void AFPSCharacter::BeginPlay()
{
	//UGameplayStatics::PlaySound2D(this, SoundTest, 1.f, 1.f); 

	UGameplayStatics::GetAllActorsOfClass(this, MusicManagerClass, MusicManagerArray);

	if (MusicManagerArray.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("We found a music manager"));
		MusicManagerRef = Cast<AMusicManager>(MusicManagerArray[0]);

		if (MusicManagerRef != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Music Manager Ref is not null"));
			//MusicManagerRef->FadeLayer(true, 1);
		}
	}


}

void AFPSCharacter::Fire()
{
	// try and fire a projectile
	if (ProjectileClass)
	{
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		FRotator MuzzleRotation = GunMeshComponent->GetSocketRotation("Muzzle");
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		//set instigator in projectile to us
		ActorSpawnParams.Instigator = this;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}


void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}