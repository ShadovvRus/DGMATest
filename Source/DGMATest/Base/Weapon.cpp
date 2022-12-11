// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::CameraComponentRequest()
{
	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetAttachParentActor());
	if (PlayerCharacter)
	{
		CameraComponent = PlayerCharacter->GetCameraComponent();
	}
}

void AWeapon::Fire()
{
	if (!CameraComponent)
	{
		CameraComponentRequest();
		if (!CameraComponent) {return;}
	}

	const UWorld* World = GetWorld();
	DrawDebugLine(
		World,
		GetActorLocation(),
		CameraComponent->GetComponentLocation()+ CameraComponent->GetForwardVector()*10000.f,
		FColor::Black,
		true,
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

