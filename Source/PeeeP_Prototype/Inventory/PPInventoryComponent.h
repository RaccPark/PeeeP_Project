// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPInventoryPartsItem.h"
#include "PPInventoryComponent.generated.h"

// �κ��丮 ���� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnChangedInventoryDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PEEEP_PROTOTYPE_API UPPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPInventoryComponent();

	virtual void InitializeComponent() override;

public:
	FOnChangedInventoryDelegate OnChangeInven;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ����
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UPPInventoryPartsItem>> PartsItems;

	// �ִ� �κ��丮 ���� ��
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 MaxInventorySlotNum;

	// ���� �� ĭ�� ���� ������ �������� ��(������ 1 ����)
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 MaxItemNum;

public:
	// Getter
	FORCEINLINE TArray<TObjectPtr<class UPPInventoryPartsItem>> GetPartsItems() { return PartsItems; }

	// ������(����) �߰�
	bool AddItem(FName InItemName, int32 InItemQuantity, int32& OutItemQuantity);
	// ������(����) ���
	void UseItem(int32 InSlotIndex);
	// ������(����) ��ü
	void SwapItem(int32 InprevIndex, int32 InCurrentIndex);

	// �κ��丮 ����
	void SortItem();

protected:
	// �κ��丮 �ʱ�ȭ
	void InitInventory();
	// ������ ����
	void RemoveItem(int32 InSlotIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
