// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGMAPlayerController.generated.h"

DECLARE_EVENT_OneParam(ADGMAPlayerController,FTurn,float Axis);
DECLARE_EVENT_OneParam(ADGMAPlayerController,FLookUp, float Axis);
DECLARE_EVENT_OneParam(ADGMAPlayerController,FMoveRight, float Axis);
DECLARE_EVENT_OneParam(ADGMAPlayerController,FMoveForward, float Axis);

DECLARE_EVENT(ADGMAPlayerController,FFire);

UCLASS()
class DGMATEST_API ADGMAPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	FTurn TurnEvent;
	FLookUp LookUpEvent;
	FMoveRight MoveRightEvent;
	FMoveForward MoveForwardEvent;
	FFire FireEvent;

protected:

	virtual void SetupInputComponent() override;
private:

	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnMoveRight(float Axis);
	void OnMoveForward(float Axis);
	void OnFire();
};
