
#include "PlayerCharacter.h"
#include "GamePlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include <Net/UnrealNetwork.h>

#include "Weapon.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter,PitchOnServer);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController=Cast<AGamePlayerController>(GetController());
	CameraComponent = FindComponentByClass<UCameraComponent>();

	FindWeapon();
	InputInitialization();
	
}

void APlayerCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		Pitch = UKismetMathLibrary::FInterpTo(Pitch, PitchOnServer, DeltaTime, 10.f);
		return;
	}

	if (!CameraComponent) {return;}

	if (GetLocalRole() == ROLE_Authority){ PitchOnServer = CameraComponent->GetComponentRotation().Pitch; }

	if (GetLocalRole() == ROLE_AutonomousProxy) { Pitch = CameraComponent->GetComponentRotation().Pitch;}

}

void APlayerCharacter::InputInitialization()
{
	if (!PlayerController) { return; }

	PlayerController->TurnEvent.AddUObject(this, &APlayerCharacter::OnTurn);
	PlayerController->LookUpEvent.AddUObject(this, &APlayerCharacter::OnLookUp);
	PlayerController->MoveForwardEvent.AddUObject(this, &APlayerCharacter::OnMoveForward);
	PlayerController->MoveRightEvent.AddUObject(this, &APlayerCharacter::OnMoveRight);
	PlayerController->FireEvent.AddUObject(this,&APlayerCharacter::OnFire);
}

void APlayerCharacter::FindWeapon()
{
	TArray<AActor*> Actors;
	GetAllChildActors(Actors, true);

	if (Actors.IsValidIndex(0)) { Weapon = Cast<AWeapon>(Actors[0]); }
}

void APlayerCharacter::UpdateHudAmmo()
{
	if (!Weapon){ FindWeapon(); }

	if (Weapon && PlayerController) { PlayerController->SetHudAmmo(Weapon->GetCurrentAmmo()); }
}

void APlayerCharacter::OnTurn(const float Axis)
{
	AddControllerYawInput(Axis);
}

void APlayerCharacter::OnLookUp(const float Axis)
{
	AddControllerPitchInput(Axis);
}

void APlayerCharacter::OnMoveForward(const float Axis)
{
	const FVector ForwardVector=GetCapsuleComponent()->GetForwardVector();
	AddMovementInput(ForwardVector, Axis);
}

void APlayerCharacter::OnMoveRight(const float Axis)
{
	const FVector RightVector = GetCapsuleComponent()->GetRightVector();
	AddMovementInput(RightVector,Axis);
}

void APlayerCharacter::OnFire()
{
	Server_Fire();
}

void APlayerCharacter::Server_Fire_Implementation()
{
	if (Weapon)
	{
		Weapon->Fire();
	}
}


bool APlayerCharacter::AddAmmo(float Ammo)
{
	if (Weapon)
	{
		Weapon->AddAmmo(Ammo);
		return true;
	}

	return false;
}


