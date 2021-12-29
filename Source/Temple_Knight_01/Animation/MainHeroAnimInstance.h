// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainHeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLE_KNIGHT_01_API UMainHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable,Category = "Aura_AnimProps")
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Aura_Movement")
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura_Movement")
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura_Movement")
	APawn* Pawn;
};
