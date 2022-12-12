// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UCameraComponent;
class APlayerCharacter;
UCLASS()
class DGMATEST_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	void Fire();
	void AddAmmo(float AddAmmo);
	float GetCurrentAmmo() const { return Ammo; }

protected:
	virtual void BeginPlay() override;

private:

	void CameraComponentRequest();

	UFUNCTION()
	void OnRep_UpdateAmmo() const;

	UPROPERTY(ReplicatedUsing= OnRep_UpdateAmmo)
	float Ammo = 10;

	UPROPERTY()
	UCameraComponent* CameraComponent{};
	UPROPERTY()
	APlayerCharacter* PlayerCharacter{};
};
