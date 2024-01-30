// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Rifle.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "C_WB_Crosshair.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

#include "C_Bullet.h"

#include "CppMacro.h"


// Sets default values
AC_Rifle::AC_Rifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root, Mesh
	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, SkeletalMeshComponent, TEXT("Mesh"), Root);
	
	// Skeletal Mesh
	CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	// Crosshair
	CppMacro::GetClass<UC_WB_Crosshair>(&CrosshairClass, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Scene2/Weapons/UI/BP_WB_Crosshair.BP_WB_Crosshair_C'"));

	// Montages
	CppMacro::GetObject<UAnimMontage>(EquipMontage, TEXT("/Script/Engine.AnimMontage'/Game/Scene2/Animations/Rifle/AM_Rifle_Equip.AM_Rifle_Equip'"));
	CppMacro::GetObject<UAnimMontage>(UnequipMontage, TEXT("/Script/Engine.AnimMontage'/Game/Scene2/Animations/Rifle/AM_Rifle_Unequip.AM_Rifle_Unequip'"));
	CppMacro::GetObject<UAnimMontage>(AttackMontage, TEXT("/Script/Engine.AnimMontage'/Game/Scene2/Animations/Rifle/AM_Rifle_Fire_Hip.AM_Rifle_Fire_Hip'"));

	// Bullet
	CppMacro::GetClass(&BulletClass, TEXT("/Script/Engine.Blueprint'/Game/Scene2/Weapons/BP_Bullet.BP_Bullet_C'"));
}

// Called when the game starts or when spawned
void AC_Rifle::BeginPlay()
{
	Super::BeginPlay();

	// Get Owner
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	// Spawn Crosshair
	Crosshair = CreateWidget<UC_WB_Crosshair>(GetWorld(), CrosshairClass);
	//Crosshair = CreateWidget<UC_WB_Crosshair>(OwnerCharacter->GetController<APlayerController>(), CrosshairClass);
	Crosshair->AddToViewport();
}

// Called every frame
void AC_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AC_Rifle* AC_Rifle::Spawn(ACharacter* InOwner)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = InOwner;
	SpawnParams.Instigator = InOwner->GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = InOwner->GetActorLocation();
	FRotator SpawnRotation = InOwner->GetActorRotation();

	AC_Rifle* Rifle = InOwner->GetWorld()->SpawnActor<AC_Rifle>(AC_Rifle::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	Rifle->AttachToComponent(InOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Rifle->BackSocket);

	return Rifle;
}

void AC_Rifle::Equip()
{
	UE_LOG(LogTemp, Log, TEXT("Rifle Equip"));
	OwnerCharacter->PlayAnimMontage(EquipMontage);
	Crosshair->CrosshairVisible();
}

void AC_Rifle::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("Rifle UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
	Crosshair->CrosshairInvisible();
}

void AC_Rifle::GrabRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AC_Rifle::BackRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
}

void AC_Rifle::UpdateCrosshair(bool bEnemyInSight)
{
	if (bEnemyInSight) Crosshair->EnemyInCrosshair();
	else Crosshair->EnemyOutCrosshair();
}

void AC_Rifle::Attack(FVector _Trajectory)
{
	OwnerCharacter->PlayAnimMontage(AttackMontage);

	// ÃÑ±¸À§Ä¡ ÀúÀå
	FVector MuzzleSocketLocation = SkeletalMeshComponent->GetSocketLocation("Muzzle");

	// ÃÑ¾Ë ±ËÀû °è»ê
	FVector Direction = _Trajectory - MuzzleSocketLocation;
	Direction.Normalize();

	// ÃÑ¾Ë »ý¼º
	AC_Bullet* Bullet = GetWorld()->SpawnActor<AC_Bullet>(BulletClass);
	Bullet->Fire(MuzzleSocketLocation, Direction, OwnerCharacter);
}

void AC_Rifle::SpecialAction()
{

}

