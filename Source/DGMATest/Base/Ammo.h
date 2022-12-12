// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class DGMATEST_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAmmo();

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	float Ammo = 20;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};
