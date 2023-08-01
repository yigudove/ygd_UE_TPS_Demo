// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "DemoItem.generated.h"

UENUM()
enum class EItemState : uint8
{
	EItemState_Drop UMETA(DisplayName = "Drop"),
	EItemState_Falling UMETA(DisplayName = "Falling"),
	EItemState_Equipped UMETA(DisplayName = "Equipped"),
	EItemState_InInventory UMETA(DisplayName = "InInventory"),
};

UCLASS()
class YGD_TPS_DEMO_API ADemoItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADemoItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Item Properties

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemState ItemState;

#pragma endregion

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	/* Skeleta Mesj for the item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Components", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* DropInfoWidget;

	/* Enable player interact area. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Components", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* InteractAreaSphere;

	float InteractAreaSphereRadius;

protected:
	UFUNCTION()
	void OnInteractAreaStartOverlap(
	UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractAreaeEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void SwitchItemProperty(EItemState State);

	bool bFalling;
	FTimerHandle ItemFallingTimer;
	float ItemFallingTime;
public:
	void ItemStartFalling();
private:
	void ItemStopFalling();

public:
	FORCEINLINE UWidgetComponent* GetDropInfoWidget() const { return DropInfoWidget; }
	FORCEINLINE USphereComponent* GetInteractAreaSphere() const{ return InteractAreaSphere; }
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }

	void SetItemState(EItemState State);
};
