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

		// �ش� ������ Ÿ��(�� ������Ʈ������ ����)�� �פ����丮�� �� ĭ ã�� ������ �߰��ϱ�
		// �� ������Ʈ������ ������ Ÿ���� ������ �ְ�, �κ��丮 ���� ���� ������ �ֱ⿡ �׳� �κ��丮 ���Կ� �ϳ� �߰��Ѵٰ� ���� �ȴ�.
		int32 Index = 0;
		for (UPPInventoryPartsItem* Item : PartsItems)
		{
			if (!IsValid(Item))
			{
				PartsItems[Index] = NewItem;	// ?
				bIsResult = true;
				OnChangeInven.Broadcast();
				break;
			}
			Index++;
		}

		if (!bIsResult)
		{
			OutItemQuantity = NewItem->ItemQuantity;
			return bIsResult;
		}
		else
		{
			return bIsResult;
		}
	}

	OutItemQuantity = InItemQuantity;
	return bIsResult;
}

void UPPInventoryComponent::UseItem(int32 InSlotIndex)
{
	/// ������ ��� �Լ������� ������ ������ Ÿ�԰� �ε����� �޾ƿͼ� �ش� �κ��丮�� �������� ����ϴ� ������ �߰��� ���Դϴ�.
	/// �����ε� �Һ� �����۸� ����� �� ������ Ȥ�� ���� Switch���� ����� Ÿ�Ժ��� ������ �������ֵ��� �����߽��ϴ�. (ex.���� ���� ��)
	/// ������ ��� �Լ��� ���� ���ȿ� �ݿ��� ���� ���� �� ���� �÷��̾��� �Լ��� ȣ���ϴ� ������ ���� ������ ��ҽ��ϴ�.
	/// �Һ� ������ ��� �� ������ ���ҽ�Ű��, ���� ���� ���� 0�̶�� �ش� �������� �Ҹ�����ֵ��� �Ͽ����ϴ�.
	/// https://velog.io/@apth1023/13.-12.-%EC%95%84%EC%9D%B4%ED%85%9C-%EC%9D%B8%EB%B2%A4%ED%86%A0%EB%A6%AC-%EC%8B%9C%EC%8A%A4%ED%85%9C-2
	
	if (PartsItems.IsValidIndex(InSlotIndex) && IsValid(PartsItems[InSlotIndex]))
	{
		// ������ �پ��� �� ������, �ƴϸ� ����Ѵٴ� flag�� �� �������� ���� ����
		// ��� ���� ���̸� ������ flag�ϴ� ���� �±��ѵ� �ϴ� ������ �Ѵٰ� ����.
		// PartsItems[InSlotIndex]->ItemQuantity--;
		
		// ������ ���
		UE_LOG(LogTemp, Warning, TEXT("Parts Item Use"));

		// ������ 0 ���϶�� �Ҹ�����ִ� �κ�
		// �� ������Ʈ������ ������ �Ҹ�Ǹ� �ȵǹǷ� �������� ����.
	}
}

void UPPInventoryComponent::RemoveItem(int32 InSlotIndex)
{
	if (PartsItems.IsValidIndex(InSlotIndex) && IsValid(PartsItems[InSlotIndex]))
	{
		PartsItems[InSlotIndex] = nullptr;
	}
}

void UPPInventoryComponent::SwapItem(int32 InprevIndex, int32 InCurrentIndex)
{
	// ���� �κ��丮 ������ ��ü ����� ���� �� ���� ����
}

void UPPInventoryComponent::SortItem()
{
	// ���� �κ��丮 ������ ���� ��� ���� ����
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
					FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets.FindByKey(Key)[0]));
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



// Called every frame
void UPPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

