// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {Reloading, Aiming, Locked, NoAmmo};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;
	void AimAt(FVector HitLocation);
	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRemainingRounds() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
	void MoveBarrelTowards(FVector AimDirection);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsBarrelMoving();
	void DecrementRemainingRounds();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	double LastFireTime = 0.0;
	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RemainingRounds = 5;
};
