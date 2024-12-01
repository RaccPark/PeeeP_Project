// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPPartsDataBase.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_Parts,	// ����
};

/**
 * 
 */

UCLASS()
class PEEEP_PROTOTYPE_API UPPPartsDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMesh> PartsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInputMappingContext> PartsMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UPPPartsBase> PartsComponent;

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	// ������ Ÿ��(���� ����), ���� Ȯ���ؾߵǴµ� �׷��� �ڵ� �� �� ���ƾ���ߵ�.
	// �Ƹ� �⺻ ������ Ŭ������ �ְ� �װ��� ������ ��ӹ޴� ��������
	UPROPERTY(EditAnywhere, Category = Base)
	EItemType ItemType;

	// ������ �̹���
	UPROPERTY(EditAnywhere, Category = Base)
	TObjectPtr<UTexture2D> ItemTexture;

	// ������ �̸�
	UPROPERTY(EditAnywhere, Category= Base)
	FString ItemName;
};
