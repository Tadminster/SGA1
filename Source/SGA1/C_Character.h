#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "C_Character.generated.h"

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
	// ��������
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	// ī�޶�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;

	// MappingContext
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// Move Input Action
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Move Input Action
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UAnimBlueprint* AnimBlueprintAsset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bEquipWeapon;

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

	// Called for movement input
	void Move(const FInputActionValue& Value);

	// Called for looking input
	void Look(const FInputActionValue& Value);
};
