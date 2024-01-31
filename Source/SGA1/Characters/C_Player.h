#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Characters/C_Prototype.h"
#include "Characters/I_Character.h"

#include "GenericTeamAgentInterface.h"

#include "Logging/LogMacros.h"
#include "C_Player.generated.h"

UENUM(BlueprintType)
enum class EPlayerWeapon : uint8
{
	Unarmed, Sword, Rifle
};

class USkeletalMesh;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class AC_Sword;
class AC_Rifle;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class SGA1_API AC_Player : public AC_Prototype, public II_Character, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	// SkeletalMesh
	//UPROPERTY(EditDefaultsOnly)
	//USkeletalMesh* SkeletalMesh;

	// SpringArm
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;

	// MappingContext
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// Move IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Jump IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Look IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	// WalkSlow IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* WalkSlowAction;

	// WalkFast IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* WalkFastAction;

	// Attack IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	// Press 1 IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Press1Action;

	// Press 2 IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Press2Action;

	// ABP
	UPROPERTY(EditAnywhere, Category = "Input")
	UAnimBlueprint* AnimBlueprintAsset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bEquipWeapon;

	UPROPERTY(EditDefaultsOnly)
	EPlayerWeapon PlayerWeapon{ EPlayerWeapon::Unarmed };

	UPROPERTY(EditDefaultsOnly)
	uint8 TeamID{ 0 };

private:
	//AC_Sword*	Sword;
	AC_Rifle*	Rifle;
	FVector		Trajectory;		// Åºµµ(±ËÀû)
	AActor*		Target;			// ¶óÀÌÇÃ °ø°Ý Å¸°Ù


public:
	int32 AttackStack{ 0 }; // °ø°Ý½ºÅÃ

public:
	// Sets default values for this character's properties
	AC_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bind input functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void WalkSlow();
	void WalkNormal();
	void WalkFast();
	//virtual void Attack(const FInputActionValue& Value) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	UFUNCTION(BlueprintCallable)
	virtual void ChangeMeshColor_Implementation(const FLinearColor& Color) override;
	//virtual AC_Sword* GetSword_Implementation() override;
	virtual void Attack() override;

	// Equip & Unequip Sword
	void EquipSword();
	void EquipRifle();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbEquipWeapon() const { return bEquipWeapon; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerWeapon GetPlayerWeaponState() const { return PlayerWeapon; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE AC_Rifle* GetRifle() { return Rifle; };

	UFUNCTION(BlueprintCallable)
	void SetUnarmed();
};
