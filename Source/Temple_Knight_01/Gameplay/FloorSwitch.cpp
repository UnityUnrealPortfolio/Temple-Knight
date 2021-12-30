// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Aura Root"));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aura Floor Switch"));
	FloorSwitch->SetupAttachment(GetRootComponent());
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aura Door"));
	Door->SetupAttachment(GetRootComponent());
	
	//Trigger Box set up
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Aura TriggerBox"));
	TriggerBox->SetupAttachment(GetRootComponent());
	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));
	//Trigger Box Collision and physics Set up
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	//set up overlap events
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnEndOverlap);

	//set up door and floor switch initial locations
	InitialDoorLocation = Door->GetComponentLocation();
	InitialFloorSwitchLocation = FloorSwitch->GetComponentLocation();
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside OnBeginOverlap()"));
	RaiseDoor();
	LowerFloorSwitch();
}

void AFloorSwitch::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside OnEndOverlap()"));
	LowerDoor();
	RaiseFloorSwitch();
}

void AFloorSwitch::UpdateDoorLocation(float Z)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation.Z = Z;
	Door->SetWorldLocation(NewLocation, false);
}

void AFloorSwitch::UpdateFloorSwitchLocation(float Z)
{
	FVector NewLocation = InitialFloorSwitchLocation;
	NewLocation.Z = Z;
	FloorSwitch->SetWorldLocation(NewLocation, false);
}


