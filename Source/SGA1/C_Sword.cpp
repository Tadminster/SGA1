// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Sword.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

#include "CppMacro.h"

// Sets default values
AC_Sword::AC_Sword() : 
	OwnerCharacter(nullptr), 
	AttackCurStage(0), AttackMaxStage(3), ComboTime(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, SkeletalMeshComponent, TEXT("Mesh"), Root);

	FString SkeletalMeshPath = TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Silly_Weapons/Blade_Balloon/SK_Blade_Balloon.SK_Blade_Balloon'");
	CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, SkeletalMeshPath);
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	// attack montages
	FString AttackMontagePath = TEXT("AnimMontage'/Game/Characters/Mannequins/Animations/Manny/AM_SwordAndShield_Attack.AM_SwordAndShield_Attack'");
	CppMacro::GetObject<UAnimMontage>(AttackMontage, AttackMontagePath);

	FString EquipMontagePath = TEXT("AnimMontage'/Game/Scene2/Animations/AM_DrawSword.AM_DrawSword'");
	CppMacro::GetObject<UAnimMontage>(EquipMontage, EquipMontagePath);

	// unequip montages
	FString UnequipMontagePath = TEXT("AnimMontage'/Game/Scene2/Animations/AM_SheathSword.AM_SheathSword'");
	CppMacro::GetObject<UAnimMontage>(UnequipMontage, UnequipMontagePath);
}

// Called when the game starts or when spawned
void AC_Sword::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Owner
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}



void AC_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ComboTime > 0.0f)
	{
		ComboTime -= DeltaTime;
		if (ComboTime <= 0.0f) AttackCurStage = 0;
	}
}

AC_Sword* AC_Sword::Spawn(ACharacter* InOwner)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = InOwner;
	SpawnParams.Instigator = InOwner->GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = InOwner->GetActorLocation();
	FRotator SpawnRotation = InOwner->GetActorRotation();

	AC_Sword* Sword = InOwner->GetWorld()->SpawnActor<AC_Sword>(AC_Sword::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	Sword->AttachToComponent(InOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Sword->SheathSocket);

	return Sword;
}

void AC_Sword::Equip()
{
	UE_LOG(LogTemp, Log, TEXT("Sword Equip"));
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void AC_Sword::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("Sword UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}

void AC_Sword::GrabSword()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AC_Sword::SheathSword()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SheathSocket);
}


void AC_Sword::Attack()
{
	if (!bCanAttack) return;
	else bCanAttack = false;

	switch (AttackCurStage)
	{
		case 0: OwnerCharacter->PlayAnimMontage(AttackMontage, 1.0f, FName("Attack1")); break;
		case 1: OwnerCharacter->PlayAnimMontage(AttackMontage, 1.0f, FName("Attack2")); break;
		case 2: OwnerCharacter->PlayAnimMontage(AttackMontage, 1.0f, FName("Attack3")); break;
	}

	AttackCurStage++;
	ComboTime = 2.0f;

	if (AttackCurStage == AttackMaxStage) AttackCurStage = 0;
}

