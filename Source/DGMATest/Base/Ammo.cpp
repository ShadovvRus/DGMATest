// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include <Components/BoxComponent.h>

#include "PlayerCharacter.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) {return;}

	UBoxComponent* BoxComponent=FindComponentByClass<UBoxComponent>();

	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AAmmo::OnBeginOverlap);
	}
}

void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	APlayerCharacter* PlayerCharacter=Cast<APlayerCharacter>(OtherActor);

	if (!PlayerCharacter){return;}

	const bool bAmmo=PlayerCharacter->AddAmmo(Ammo);

	if (bAmmo) { Destroy(); }
	
}

