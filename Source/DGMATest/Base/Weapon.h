// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class DGMATEST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void Fire();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void CameraComponentRequest();

	UPROPERTY()
	UCameraComponent* CameraComponent{};
};
