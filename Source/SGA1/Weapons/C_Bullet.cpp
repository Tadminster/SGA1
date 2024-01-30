// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CppMacro.h"

// Sets default values
AC_Bullet::AC_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Mesh
	CppMacro::CreateComponet(this, Mesh, TEXT("BulletMesh"), RootComponent);
	Mesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	RootComponent = Mesh;

	// Movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	//Movement = CppMacro::GetComponent<UProjectileMovementComponent>(this);
	Movement->InitialSpeed = 5000.f;
	Movement->MaxSpeed = 5000.f;
	Movement->ProjectileGravityScale = 0.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;
	Movement->Bounciness = 0.f;
	Movement->Friction = 0.f;

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AC_Bullet::Fire(FVector _Location, FVector _Direction, AActor* _IgnoredActor)
{
	SetActorLocation(_Location);
	Movement->Velocity = _Direction * Movement->InitialSpeed;

	if (_IgnoredActor)
	{
		// 총알의 Mesh가 IgnoredActor와의 충돌을 무시하도록 설정
		Mesh->MoveIgnoreActors.Add(_IgnoredActor); 
	}
}

