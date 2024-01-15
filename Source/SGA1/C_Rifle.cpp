// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Rifle.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

#include "CppMacro.h"


// Sets default values
AC_Rifle::AC_Rifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, SkeletalMeshComponent, TEXT("Mesh"), Root);
	
	FString SkeletalMeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'");
	CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, SkeletalMeshPath);
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	// attack montages
	//FString AttackMontagePath = TEXT("AnimMontage'/Game/Characters/Mannequins/Animations/Manny/AM_SwordAndShield_Attack.AM_SwordAndShield_Attack'");
	//CppMacro::GetObject<UAnimMontage>(AttackMontage, AttackMontagePath);

	// equip montages
	FString EquipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Scene2/Animations/AM_EquipRifle.AM_EquipRifle'");
	CppMacro::GetObject<UAnimMontage>(EquipMontage2, EquipMontagePath);

	// unequip montages
	FString UnequipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Scene2/Animations/AM_UnequipRifle.AM_UnequipRifle'");
	CppMacro::GetObject<UAnimMontage>(UnequipMontage2, UnequipMontagePath);
}

// Called when the game starts or when spawned
void AC_Rifle::BeginPlay()
{
	Super::BeginPlay();

	// Get Owner
	OwnerCharacter = Cast<ACharacter>(GetOwner());
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
	OwnerCharacter->PlayAnimMontage(EquipMontage2);
}

void AC_Rifle::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("Rifle UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage2);
}

void AC_Rifle::GrabRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AC_Rifle::BackRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);
}

