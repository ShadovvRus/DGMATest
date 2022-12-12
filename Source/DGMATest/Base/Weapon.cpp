// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(GetAttachParentActor());
}

void AWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, Ammo);
}


void AWeapon::CameraComponentRequest()
{
	if (PlayerCharacter)
	{
		CameraComponent = PlayerCharacter->GetCameraComponent();
	}
}

void AWeapon::OnRep_UpdateAmmo() const
{
	if (PlayerCharacter) { PlayerCharacter->UpdateHudAmmo(); }
}

void AWeapon::Fire()
{
	if (Ammo<=0.f){return;}

	if (!CameraComponent)
	{
		CameraComponentRequest();
		if (!CameraComponent) {return;}
	}

	Ammo--;

	const UWorld* World = GetWorld();
	DrawDebugLine(
		World,
		GetActorLocation(),
		CameraComponent->GetComponentLocation()+ CameraComponent->GetForwardVector()*10000.f,
		FColor::Black,
		false,
		1);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetAttachParentActor());

	FHitResult HitResult{};
	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 10000.f,
		ECC_Camera,
		CollisionQueryParams);

	if (bHit&& Cast<APlayerCharacter>(HitResult.GetActor()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit"));
	}
}

void AWeapon::AddAmmo(float AddAmmo)
{
	Ammo += AddAmmo;
}

