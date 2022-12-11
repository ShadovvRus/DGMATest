// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

