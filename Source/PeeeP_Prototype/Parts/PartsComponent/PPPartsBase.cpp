// Fill out your copyright notice in the Description page of Project Settings.


#include "Parts/PartsComponent/PPPartsBase.h"
#include "Parts/PartsData/PPGrabPartsData.h"

#include "Character/PPCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPPPartsBase::UPPPartsBase()
{
	//�׻� true�� �����ؾ� ��. false ������, TickFunction�� ��� ��ü�� ���ƹ����� ������,����� Tick�� ������� ���� ��쿡�� false�� ������.
	PrimaryComponentTick.bCanEverTick = true; 

	//Tick�� ���������� ���� ������.
	//PrimaryComponentTick.bStartWithTickEnabled = false;

	Owner = Cast<APPCharacterPlayer>(GetOwner()); 
}


//void UPPPartsBase::OnComponentDestroyed(bool bDestroyingHierarchy)
//{
//	// ?????? ?????(with Github Copilot)
//	Super::OnComponentDestroyed(bDestroyingHierarchy);
//
//	APPCharacterPlayer* PlayerCharacter = Cast<APPCharacterPlayer>(GetOwner());
//	if (PlayerCharacter)
//	{
//		APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
//		if (!PlayerController)
//		{
//			PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//		}
//		if (PlayerController)
//		{
//			if (UEnhancedInputLocalPlayerSubsystem* Subsystem
//				= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//			{
//				if (PartsData)
//				{
//					Subsystem->RemoveMappingContext(PartsData->PartsMappingContext);
//				}
//			}
//		}
//	}
//}

void UPPPartsBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	// ?????? ????(with Github Copilot)
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	APPCharacterPlayer* PlayerCharacter = Cast<APPCharacterPlayer>(GetOwner());
	if (PlayerCharacter)
	{
		APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
		if (!PlayerController)
		{
			return;
		}
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (PartsData)
			{
				Subsystem->RemoveMappingContext(PartsData->PartsMappingContext);
			}
		}
	}
}

// Called when the game starts
void UPPPartsBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPPPartsBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


