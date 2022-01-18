// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class TEMPLE_KNIGHT_01_API AFloorSwitch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloorSwitch();

	//volume to trigger event when character overlaps it
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwitch")
		class UBoxComponent* TriggerBox;

	//Switch for character to step on to open/close door
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwitch")
		class UStaticMeshComponent* FloorSwitch;

	//The door to open/close in response to the switch activation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwith")
		class UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwitch")
		FVector InitialDoorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwitch")
		FVector InitialFloorSwitchLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura_FloorSwitch")
		float SwitchTime;

	FTimerHandle SwitchTimerHandle;

	bool bIsOverlappingSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Aura_FloorSwitch")
		void RaiseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Aura_FloorSwitch")
		void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Aura_FloorSwitch")
		void LowerFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "Aura_FloorSwitch")
		void RaiseFloorSwitch();

	UFUNCTION(BlueprintCallable, Category = "Aura_FloorSwitch")
		void UpdateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable, Category = "Aura_FloorSwitch")
		void UpdateFloorSwitchLocation(float Z);

	void CloseDoor();


};
