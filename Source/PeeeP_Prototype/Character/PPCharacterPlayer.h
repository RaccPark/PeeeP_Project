// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPCharacterBase.h"
#include "InputActionValue.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Interface/UI/PPElectricHUDInterface.h"
#include "Interface/PPAnimationGrabInterface.h"
#include "PPCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PEEEP_PROTOTYPE_API APPCharacterPlayer : public APPCharacterBase, public IPPElectricHUDInterface , public IPPAnimationGrabInterface
{
	GENERATED_BODY()	
	
public:
	APPCharacterPlayer();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Character Control Section
protected:
	// Character Movement Component
	// �ܺο� ���ؼ� �÷��̾ ������ ���� ���� �� �������κ��� �����Ͽ� ���
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCharacterMovementComponent> CharacterMovementComponent;

	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UPPCharacterControlData* CharacterControlData) override;

// �Է� ����
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ButtonInteract;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ButtonInteraction(const FInputActionValue& Value);

	ECharacterControlType CurrentCharacterControlType;

protected:
	// Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

public:
	UCameraComponent* GetCamera();


protected:
//Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> GrabAnimMontage;


//Parts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parts, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPPPartsBase> Parts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parts, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> AttachedMesh;

	//임시
	TArray<TObjectPtr<class UPPPartsBase>> PartsArray;

public:
	void SwitchParts(class UPPPartsDataBase* InPartsData);
	void AddParts(class UActorComponent* InComponent);

	virtual void GrabHitCheck() override;
	void SetAttachedMesh(class UPPPartsBase* InParts);

	
protected:
//ElectricComponent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Electric, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ElectricDischargeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Electric, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ElectricDischargeModeChangeAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Electric)
	TObjectPtr<class UPPElectricDischargeComponent> ElectricDischargeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Electric)
	TObjectPtr<class UNiagaraComponent> PlayerCharacterNiagaraComponent;

	float ChargeTime;
	float MaxWalkSpeed;

public:
	void ReduationMaxWalkSpeedRatio(float InReductionRatio);
	void RevertMaxWalkSpeed();


	class UNiagaraComponent* GetPlayerCharacterNiagaraComponent() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> OpenMenuInteract;

	void OpenMenu();

public:
	// ElectricDischargeComponent
	UPPElectricDischargeComponent* GetElectricDischargeComponent();

};
