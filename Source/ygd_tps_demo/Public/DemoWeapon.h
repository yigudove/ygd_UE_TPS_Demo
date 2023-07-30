// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoItem.h"
#include "DemoWeapon.generated.h"

UENUM(BlueprintType)
enum class EAmmoType :uint8
{
	EAmmoType_9mm UMETA(DisplayName = "9mm"),
	EAmmoType_AR UMETA(DisplayName = "AR")
};

UENUM(BlueprintType)
enum class EFireMode :uint8
{
	EFireMode_Auto UMETA(DisplayName = "Auto"),
	EFireMode_SemiAuto UMETA(DisplayName = "SemiAuto")
};

UCLASS()
class YGD_TPS_DEMO_API ADemoWeapon : public ADemoItem
{
	GENERATED_BODY()
public:
	ADemoWeapon();

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EFireMode WeaponFireMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 AmmoAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 BulletMaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float ReloadingAmmoTime;

public:
	FORCEINLINE EFireMode GetWeaponFireMode() const { return WeaponFireMode; }
	void SetWeaponFireMode(EFireMode NewWeaponFireMode);

	FORCEINLINE int32 GetAmmoAmount() const { return AmmoAmount; }
	FORCEINLINE int32 GetBulletMaxAmmo() const { return BulletMaxAmmo; }
	FORCEINLINE float GetReloadingAmmoTime() const { return ReloadingAmmoTime; }

	/* Called when fire weapon. */
	void DecrementAmmoAmount(int32 DecrementAmount);
	void ReloadAmmo(int32 ReloadAmmoAmount);
};
