// Fill out your copyright notice in the Description page of Project Settings.


#include "DGMAPlayerController.h"

void ADGMAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Turn",this,&ADGMAPlayerController::OnTurn);
	InputComponent->BindAxis("LookUp", this,&ADGMAPlayerController::OnLookUp );
	InputComponent->BindAxis("MoveRight", this, &ADGMAPlayerController::OnMoveRight);
	InputComponent->BindAxis("MoveForward", this, &ADGMAPlayerController::OnMoveForward);
	InputComponent->BindAction("Fire",IE_Pressed,this,&ADGMAPlayerController::OnFire);
}

void ADGMAPlayerController::OnTurn(float Axis)
{
	TurnEvent.Broadcast(Axis);
}

void ADGMAPlayerController::OnLookUp(float Axis)
{
	LookUpEvent.Broadcast(Axis);
}

void ADGMAPlayerController::OnMoveRight(float Axis)
{
	MoveRightEvent.Broadcast(Axis);
}

void ADGMAPlayerController::OnMoveForward(float Axis)
{
	MoveForwardEvent.Broadcast(Axis);
}

void ADGMAPlayerController::OnFire()
{
	FireEvent.Broadcast();
}
