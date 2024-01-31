// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_Player.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/SkeletalMesh.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "Weapons/C_Sword.h"
#include "Weapons/C_Rifle.h"

#include "CppMacro.h"
#include "C_Player.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AC_Player::AC_Player():
	bEquipWeapon(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Skeletal Mesh
	FString MeshPath = TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'");
	CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, MeshPath);
	GetMesh()->SetSkeletalMesh(SkeletalMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // Pitch, Yaw, Roll

	// SpringArm
	CppMacro::CreateComponet<USpringArmComponent>(this, SpringArm, TEXT("SpringArm"), GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controlle
	SpringArm->SetRelativeLocation(FVector(50, 50, 50));
	SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
	
	// Camera
	CppMacro::CreateComponet<UCameraComponent>(this, Camera, TEXT("Camera"), SpringArm);


	// Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	FString AnimBlueprintPath = TEXT("AnimBlueprint'/Game/Scene2/Animations/ABP_Character.ABP_Character'");
	CppMacro::GetObject<UAnimBlueprint>(AnimBlueprintAsset, AnimBlueprintPath);
	GetMesh()->SetAnimInstanceClass(AnimBlueprintAsset->GeneratedClass);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	FString ImcPath = TEXT("InputMappingContext'/Game/Input/Default_IMC.Default_IMC'");
	CppMacro::GetObject<UInputMappingContext>(InputMappingContext, ImcPath);

	FString MoveActionPath = TEXT("InputAction'/Game/Input/IA_Move.IA_Move'");
	CppMacro::GetObject<UInputAction>(MoveAction, MoveActionPath);

	FString JumpActionPath = TEXT("InputAction'/Game/Input/IA_Jump.IA_Jump'");
	CppMacro::GetObject<UInputAction>(JumpAction, JumpActionPath);

	FString LookActionPath = TEXT("InputAction'/Game/Input/IA_Look.IA_Look'");
	CppMacro::GetObject<UInputAction>(LookAction, LookActionPath);

	FString AttackActionPath = TEXT("InputAction'/Game/Input/IA_Attack.IA_Attack'");
	CppMacro::GetObject<UInputAction>(AttackAction, AttackActionPath);

	FString WalkSlowActionPath = TEXT("InputAction'/Game/Input/IA_WalkSlow.IA_WalkSlow'");
	CppMacro::GetObject<UInputAction>(WalkSlowAction, WalkSlowActionPath);

	FString WalkFastActionPath = TEXT("InputAction'/Game/Input/IA_WalkFast.IA_WalkFast'");
	CppMacro::GetObject<UInputAction>(WalkFastAction, WalkFastActionPath);

	FString Press1ActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Press1.IA_Press1'");
	CppMacro::GetObject<UInputAction>(Press1Action, Press1ActionPath);

	FString Press2ActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Press2.IA_Press2'");
	CppMacro::GetObject<UInputAction>(Press2Action, Press2ActionPath);

	GetCharacterMovement()->MaxWalkSpeed = 300.f;


}

// Called when the game starts or when spawned
void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem 
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// Spawn Sword
	Sword = AC_Sword::Spawn(this);
	Rifle = AC_Rifle::Spawn(this);
}

// Called every frame
void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Targeting
	FHitResult HitResult;										// 충돌 정보를 담을 변수
	FVector Start = Camera->GetComponentLocation();				// 카메라 위치
	FVector End = Start + Camera->GetForwardVector() * 10000.f;	// 카메라 위치에서 카메라가 바라보는 방향으로 10000만큼 떨어진 위치
	Trajectory = End;
	FCollisionQueryParams CollisionParams;						// 충돌에 대한 정보를 담을 변수
	CollisionParams.AddIgnoredActor(this);						// 자기 자신은 검사에서 제외
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);	// 충돌 검사
	if (bHit)
	{
		Target = HitResult.GetActor(); // 충돌한 Actor를 Target으로 설정
	}
	else
	{
		Target = nullptr;
	}


	if (PlayerWeapon == EPlayerWeapon::Rifle)
	{
		// 바닥과 충돌은 제외
		if (bHit && Target->GetName() == "Floor")
		{
			Rifle->UpdateCrosshair(false);
		}
		else Rifle->UpdateCrosshair(bHit);
	}


}

// Called to bind functionality to input
void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// '1' 키에 대한 이벤트 처리
	//PlayerInputComponent->BindKey(EKeys::One, IE_Pressed, this, &AC_Player::EquipSword);
	//PlayerInputComponent->BindKey(EKeys::Two, IE_Pressed, this, &AC_Player::EquipRifle);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	 {
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_Player::Move);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_Player::Look);

		// Walk Slow
		EnhancedInputComponent->BindAction(WalkSlowAction, ETriggerEvent::Started, this, &AC_Player::WalkSlow);
		EnhancedInputComponent->BindAction(WalkSlowAction, ETriggerEvent::Completed, this, &AC_Player::WalkNormal);

		// Walk Fast
		EnhancedInputComponent->BindAction(WalkFastAction, ETriggerEvent::Started, this, &AC_Player::WalkFast);
		EnhancedInputComponent->BindAction(WalkFastAction, ETriggerEvent::Completed, this, &AC_Player::WalkNormal);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AC_Player::Attack);

		// Press1 (Sword)
		EnhancedInputComponent->BindAction(Press1Action, ETriggerEvent::Started, this, &AC_Player::EquipSword);

		// Press2 (Rifle)
		EnhancedInputComponent->BindAction(Press2Action, ETriggerEvent::Started, this, &AC_Player::EquipRifle);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AC_Player::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("Move called: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get camera forward vector
		//const FVector ForwardDirection = Camera->GetForwardVector();
		const FVector ForwardDirection = GetActorForwardVector();

		// get right vector 
		const FVector RightDirection = Camera->GetRightVector();

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AC_Player::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("Look called: X=%f, Y=%f"), LookAxisVector.X, LookAxisVector.Y);

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC_Player::EquipSword()
{
	// 무기를 장착 중일 때,
	if (bEquipWeapon)
	{
		if (PlayerWeapon == EPlayerWeapon::Sword)
		{
			// 장착 해제
			Sword->UnEquip();
		}
		// 해당 무기가 총이면
		else if (PlayerWeapon == EPlayerWeapon::Rifle)
		{
			// 장착 해제
			Rifle->UnEquip();
		}

		// 무기를 장착 중이 아니게 설정
		bEquipWeapon = false;
		PlayerWeapon = EPlayerWeapon::Unarmed;
	}
	// 무기를 장착 중이 아닐 때,
	else
	{
		// 검을 장착
		Sword->Equip();

		// 무기를 장착 중이게 설정
		bEquipWeapon = true;
		PlayerWeapon = EPlayerWeapon::Sword;
	}
}

void AC_Player::EquipRifle()
{
	// 무기를 장착 중일 때,
	if (bEquipWeapon)
	{
		// 해당 무기가 총이면
		if (PlayerWeapon == EPlayerWeapon::Rifle)
		{
			// 장착 해제
			Rifle->UnEquip();
			SpringArm->SetRelativeLocation(FVector(50, 50, 50));
		}
		// 해당 무기가 검이면
		else if (PlayerWeapon == EPlayerWeapon::Sword)
		{
			// 장착 해제
			Sword->UnEquip();
		}

		// 무기를 장착 중이 아니게 설정
		bEquipWeapon = false;
		PlayerWeapon = EPlayerWeapon::Unarmed;
	}
	// 무기를 장착 중이 아닐 때,
	else
	{
		// 총을 장착
		Rifle->Equip();

		SpringArm->SetRelativeLocation(FVector(200, 50, 50));

		// 무기를 장착 중이게 설정
		bEquipWeapon = true;
		PlayerWeapon = EPlayerWeapon::Rifle;
	}
}

void AC_Player::SetUnarmed()
{
	PlayerWeapon = EPlayerWeapon::Unarmed;
}

void AC_Player::WalkSlow()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void AC_Player::WalkNormal()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AC_Player::WalkFast()
{
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}


void AC_Player::Attack()
{
	if (PlayerWeapon == EPlayerWeapon::Unarmed) return;
	else if (PlayerWeapon == EPlayerWeapon::Sword) Sword->Attack();
	else if (PlayerWeapon == EPlayerWeapon::Rifle) Rifle->Attack(Trajectory);
}

FGenericTeamId AC_Player::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

void AC_Player::ChangeMeshColor_Implementation(const FLinearColor& Color)
{
	GetMesh()->SetVectorParameterValueOnMaterials(TEXT("BodyColor"), FVector(Color));
}
