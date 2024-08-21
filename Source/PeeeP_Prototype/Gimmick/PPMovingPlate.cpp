#include "PPMovingPlate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

APPMovingPlate::APPMovingPlate()
{
    PrimaryActorTick.bCanEverTick = true;

    BeltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor"));
    RootComponent = BeltMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APPMovingPlate::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APPMovingPlate::OnOverlapEnd);

    BeltSpeed = 200.0f;
    bIsActivated = false;
    bIsSwitchOn = false; // ����ġ ���¸� ��Ÿ���� ���� �ʱ�ȭ
}

void APPMovingPlate::BeginPlay()
{
    Super::BeginPlay();
}

void APPMovingPlate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsActivated && bIsSwitchOn) // �� ���°� ��� true�� ���� ������ �۵�
    {
        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorUpVector() * BeltSpeed * DeltaTime;
        SetActorLocation(NewLocation);
    }
}

void APPMovingPlate::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        UE_LOG(LogTemp, Log, TEXT("Player Overlap"));
        bIsActivated = true;
    }
}

void APPMovingPlate::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        bIsActivated = false;
    }
}

void APPMovingPlate::SetSwitchState(bool bNewState)
{
    bIsSwitchOn = bNewState;
}