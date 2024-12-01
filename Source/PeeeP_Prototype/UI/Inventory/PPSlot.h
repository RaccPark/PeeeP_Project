// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/PPCustomWidget.h"
#include "PPSlot.generated.h"

/**
 * 
 */
UCLASS()
class PEEEP_PROTOTYPE_API UPPSlot : public UPPCustomWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	// ���� �ʱ�ȭ
	void Init();
	// ���� ������Ʈ
	void UpdateSlot();

public:
	// ���Կ� ������ �̹���
	UPROPERTY(VisibleAnywhere, Category = "Slot")
	TObjectPtr<class UImage> IMG_Item;

	// ���Կ� ������ �������� ����
	UPROPERTY(VisibleAnywhere, Category = "Slot")
	TObjectPtr<class UTextBlock> TXT_Quantity;

	// ���� ������ �ε���
	UPROPERTY(EditAnywhere, Category = "Slot")
	int32 SlotIndex;

protected:
	// ���� ���� ������Ʈ �Լ�
	// �� ������Ʈ������ �� ���� �׷��� ���� ���� �� ����.
	void UpdatePartsSlot();

	// �� ĭ�� �����ϱ� ���� ���� �ؽ���
	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UTexture2D> DefaultTexture;
};
