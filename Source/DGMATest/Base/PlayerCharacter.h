// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AWeapon;
class ADGMAPlayerController;

UCLASS()
class DGMATEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UFUNCTION(BlueprintPure)
	float GetPitch() const { return Pitch; }

	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void InputInitialization();
	void FindWeapon();

	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnFire();

	UFUNCTION(Server, Reliable)
	void Server_Fire();

	UPROPERTY(Replicated)
	float PitchOnServer {};

	float Pitch{};

	UPROPERTY()
	ADGMAPlayerController* PlayerController{};

	UPROPERTY()
	AWeapon* Weapon {};

	UPROPERTY()
	UCameraComponent* CameraComponent{};
};
