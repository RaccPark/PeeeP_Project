// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/PPInventoryComponent.h"
#include "Engine/AssetManager.h"

// Sets default values for this component's properties
UPPInventoryComponent::UPPInventoryComponent()
{
	bWantsInitializeComponent = true;

	MaxInventorySlotNum = 6;
	MaxItemNum = 1;

	// �ʱ� ������ ����
	PartsItems.Init(nullptr, MaxInventorySlotNum);
}

void UPPInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// �κ��丮 �ʱ�ȭ
	InitInventory();
}


// Called when the game starts
void UPPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UPPInventoryComponent::AddItem(FName InItemName, int32 InItemQuantity, int32& OutItemQuantity)
{
	// ���������� �߰��ߴ����� ���� ��� ��ȯ�� ����
	bool bIsResult = false;

	// �ּ� �Ŵ��� �ҷ�����
	UAssetManager& Manager = UAssetManager::Get();

	// �ּ� ���̵� ����Ʈ �޾ƿ���
	TArray<FPrimaryAssetId> Assets;
	// �±� ������ �Ѱ��༭ ������ �±׸� ���� �ּµ��� ����� �迭�� ��ȯ����
	Manager.GetPrimaryAssetIdList(TEXT("PPPartsData"), Assets);

	// Ư�� ������ Ű ����
	FPrimaryAssetId Key;
	Key.PrimaryAssetType = TEXT("PPPartsData");
	Key.PrimaryAssetName = InItemName;

	// �ش� Ű�� �ּ��� �����Ѵٸ�
	if (Assets.Contains(Key))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Data"));

		// ������ ����
		UPPInventoryPartsItem* NewItem = NewObject<UPPInventoryPartsItem>();
		if (NewItem)
		{
			FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets.FindByKey(Key)[0]));
			if (AssetPtr.IsPending())
			{
				AssetPtr.LoadSynchronous();
			}
			UPPPartsDataBase* ItemData = Cast<UPPPartsDataBase>(AssetPtr.Get());
			if (ItemData)
			{
				NewItem->PartsData = ItemData;
				NewItem->ItemQuantity = InItemQuantity;
			}
			else
			{
				return bIsResult;
			}
		}
	}

}

void UPPInventoryComponent::UseItem(int32 InSlotIndex)
{
}

void UPPInventoryComponent::InitInventory()
{
	// ������ �ִ� �������� ��� ������ ���ΰ�?

	// ���� �Ŵ��� �̱��� �ҷ�����
	UAssetManager& Manager = UAssetManager::Get();

	// ���� ���̵� ����Ʈ �޾ƿ���
	TArray<FPrimaryAssetId> Assets;
	// �±� ������ �Ѱ��༭ ������ �±׸� ���� �ּµ��� ����� �迭�� ��ȯ����
	Manager.GetPrimaryAssetIdList(TEXT("PPPartsData"), Assets);

	if (Assets.Num() > 0)
	{
		TMap<int32, TPair<FName, int32>> InventoryPartsArray;
		// �׽�Ʈ ���(�����δ� ����� ���Ͽ��� �����͸� �о�;� ��)
		{
			InventoryPartsArray.Add(1, { TEXT("GrabParts"), 1 });
		}

		for (const auto& InvItem : InventoryPartsArray)
		{
			// Ư�� ������ Ű ����
			FPrimaryAssetId Key;
			Key.PrimaryAssetType = TEXT("PPPartsData");
			Key.PrimaryAssetName = InvItem.Value.Key;

			if (Assets.Contains(Key))
			{
				// ������ ����
				UPPInventoryPartsItem* NewItem = NewObject<UPPInventoryPartsItem>();
				if (NewItem)
				{
					FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets.FindByKey(Key)[0]);
					if (AssetPtr.IsPending())
					{
						AssetPtr.LoadSynchronous();
					}
					UPPPartsDataBase* ItemData = Cast<UPPPartsDataBase>(AssetPtr.Get());
					if (ItemData)
					{
						NewItem->PartsData = ItemData;
						NewItem->ItemQuantity = InvItem.Value.Value;
						// ������ �ֱ�
						PartsItems[InvItem.Key] = NewItem;
					}
				}
			}
		}

	}
}

void UPPInventoryComponent::RemoveItem(int32 InSlotIndex)
{
}

// Called every frame
void UPPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

