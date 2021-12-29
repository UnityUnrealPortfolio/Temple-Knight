// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHero.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainHero::AMainHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Aura_CameraBoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Aura_FollowCamera"));

	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookRate = 65.f;

	//do not turn character along with camera during looking up/down and turning side to side
	bUseControllerRotationYaw = false;

	//cause character to turn and face direction of movement...
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//at this velocity
	GetCharacterMovement()->RotationRate = FRotator(0.f, 570.f, 0.f);
	//set jump velocity
	GetCharacterMovement()->JumpZVelocity = 670.f;
	//set air control
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AMainHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//handle jump functionality
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released,this, &ACharacter::StopJumping);
	
	//Handle move forrward and sideways functionality
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainHero::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainHero::MoveRight);

	//Handle look functionality using gamepad,mouse(LookUp,LookSide) and 
	//using keyboard arrow keys(TurnRate,LookUpRate)
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookSide", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainHero::LookSide);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainHero::LookUp);
}

void AMainHero::MoveForward(float value)
{
	if (Controller != nullptr && value != 0.0f)
	{
		//Get the characters current forward direction taking into account where
		//he is currently facing
		const FRotator currentRotation = Controller->GetControlRotation();
		const FRotator currentYawRotation = FRotator(0.f, currentRotation.Yaw, 0.f);

		const FVector currentForwardDirection = FRotationMatrix(currentYawRotation).GetUnitAxis(EAxis::X);

		//feed that current forward direction into movement input
		AddMovementInput(currentForwardDirection, value);
	}
}

void AMainHero::MoveRight(float value)
{
	//Get the characters current right direction taking into account where
		//he is currently facing
	const FRotator currentRotation = Controller->GetControlRotation();
	const FRotator currentYawRotation = FRotator(0.f, currentRotation.Yaw, 0.f);

	const FVector currentRightDirection = FRotationMatrix(currentYawRotation).GetUnitAxis(EAxis::Y);

	//feed that current right direction into movement input
	AddMovementInput(currentRightDirection, value);
}


void AMainHero::LookUp(float value)
{
	//add input to the controller yaw
	AddControllerPitchInput(value * BaseLookRate * GetWorld()->GetDeltaSeconds());
}

void AMainHero::LookSide(float value)
{
	//add input to the controller pitch
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

