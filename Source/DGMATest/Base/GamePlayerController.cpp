// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "GameHUD.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD=Cast<AGameHUD>(GetHUD());
}


void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Turn",this,&AGamePlayerController::OnTurn);
	InputComponent->BindAxis("LookUp", this,&AGamePlayerController::OnLookUp );
	InputComponent->BindAxis("MoveRight", this, &AGamePlayerController::OnMoveRight);
	InputComponent->BindAxis("MoveForward", this, &AGamePlayerController::OnMoveForward);
	InputComponent->BindAction("Fire",IE_Pressed,this,&AGamePlayerController::OnFire);
}

void AGamePlayerController::OnTurn(float Axis)
{
	TurnEvent.Broadcast(Axis);
}

void AGamePlayerController::OnLookUp(float Axis)
{
	LookUpEvent.Broadcast(Axis);
}

void AGamePlayerController::OnMoveRight(float Axis)
{
	MoveRightEvent.Broadcast(Axis);
}

void AGamePlayerController::OnMoveForward(float Axis)
{
	MoveForwardEvent.Broadcast(Axis);
}

void AGamePlayerController::OnFire()
{
	FireEvent.Broadcast();
}

void AGamePlayerController::SetHudAmmo(float Ammo)
{
	if (HUD) {HUD->SetHudAmmo(Ammo);}
}