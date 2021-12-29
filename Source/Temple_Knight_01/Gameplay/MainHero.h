// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainHero.generated.h"

UCLASS()
class TEMPLE_KNIGHT_01_API AMainHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainHero();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aura_Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aura_Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Base rates for scaling turning and looking*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aura_Camera, meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aura_Camera, meta = (AllowPrivateAccess = "true"))
		float BaseLookRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);

	/**
	* allows character to look up/down at a given rate of degrees pa frame
	* @param value This is a normalized value where 1 == 100% of desired rate
	*/
	void LookUp(float value);

	/**
	* allows character to turn at a given rate of degrees pa frame
	* @param value This is a normalized value where 1 == 100% of desired rate
	*/
	void LookSide(float value);

	//convenience get and set for spring arm and camera
	FORCEINLINE class USpringArmComponent* GetCameraBoom() { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() { return FollowCamera; }

};
