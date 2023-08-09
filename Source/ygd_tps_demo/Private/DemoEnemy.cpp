// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoEnemy.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADemoEnemy::ADemoEnemy():
	EnemyHealth(100.f),
	EnemyMaxHealth(100.f),

	InfoWidgetDisplayTime(4.f),

	bCanHitReact(true),
	HitReactTime(0.3f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemoEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), EnemyPatrolPoint);

	DrawDebugSphere(GetWorld(), WorldPatrolPoint, 25.f, 12, FColor::Red, true);
}

// Called every frame
void ADemoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Log, TEXT("Enemy Health: %f"), EnemyHealth);

}

void ADemoEnemy::ShowInfoWidget_Implementation()
{
	GetWorldTimerManager().ClearTimer(InfoWidgetTimer);
	GetWorldTimerManager().SetTimer(InfoWidgetTimer, this, &ADemoEnemy::HideInfoWidget, InfoWidgetDisplayTime);
}

void ADemoEnemy::PlayEnemyHitMontage(FName MontageSection, float PlayRate)
{
	if (bCanHitReact)
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(EnemyHitMontage, PlayRate);
			AnimInstance->Montage_JumpToSection(MontageSection, EnemyHitMontage);

			bCanHitReact = false;

			GetWorldTimerManager().SetTimer(EnemyHitReactTimer, this, &ADemoEnemy::ResetEnemyHitReactTimer, HitReactTime);
		}
	}
}

void ADemoEnemy::ResetEnemyHitReactTimer()
{
	bCanHitReact = true;
}

void ADemoEnemy::BulletHit_Implementation(FHitResult HitResult)
{
	if (BulletHitImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHitImpactParticles, HitResult.Location, FRotator(0.f), true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy BulletHitImpactParticles lost."))
	}

	if (BulletHitSounds)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BulletHitSounds, GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy BulletHitSounds lost."))
	}

	ShowInfoWidget();

	PlayEnemyHitMontage(FName("HitReact_1"));
}



float ADemoEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvenet, AController* EvenInstigator, AActor* DamageCauser)
{
	if (EnemyHealth - DamageAmount <= 0.f)
	{
		EnemyHealth = 0.f;
		EnemyDie();
	}
	else
	{
		EnemyHealth -= DamageAmount;
	}

	return DamageAmount;
}

void ADemoEnemy::EnemyDie()
{
	HideInfoWidget();
}