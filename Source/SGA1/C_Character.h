#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "C_Character.generated.h"

UENUM(BlueprintType)
enum class EPlayerWeapon : uint8
{
	Unarmed, Sword,
};

class USkeletalMesh;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class SGA1_API AC_Character : public ACharacter
{
	GENERATED_BODY()

protected:
	// SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh;

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

	// ABP
	UPROPERTY(EditAnywhere, Category = "Input")
	UAnimBlueprint* AnimBlueprintAsset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bEquipWeapon;

	UPROPERTY(EditDefaultsOnly)
	EPlayerWeapon PlayerWeapon{ EPlayerWeapon::Unarmed };

private:
	// Sword
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	int32 AttackStage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	int32 AttackMaxStage;

	class AC_Sword* Sword;

public:
	// Sets default values for this character's properties
	AC_Character();

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
	void WalkSlow(const FInputActionValue& Value);
	void WalkNormal(const FInputActionValue& Value);
	void WalkFast(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);

	// Equip Weapon, Unequip Weapon
	void EquipWeapon();
};
