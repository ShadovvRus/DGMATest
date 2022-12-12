// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


DECLARE_EVENT_OneParam(AGamePlayerController, FTurn, float Axis);
DECLARE_EVENT_OneParam(AGamePlayerController,FLookUp, float Axis);
DECLARE_EVENT_OneParam(AGamePlayerController,FMoveRight, float Axis);
DECLARE_EVENT_OneParam(AGamePlayerController,FMoveForward, float Axis);

DECLARE_EVENT(AGamePlayerController,FFire);

class AGameHUD;

UCLASS()
class DGMATEST_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	FTurn TurnEvent;
	FLookUp LookUpEvent;
	FMoveRight MoveRightEvent;
	FMoveForward MoveForwardEvent;
	FFire FireEvent;

	void SetHudAmmo(float Ammo);

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY()
	AGameHUD* HUD{};

	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnMoveRight(float Axis);
	void OnMoveForward(float Axis);
	void OnFire();
};
