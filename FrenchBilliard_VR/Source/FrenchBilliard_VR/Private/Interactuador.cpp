// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactuador.h"
#include "InteractComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AInteractuador::AInteractuador()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    InteractComp = CreateDefaultSubobject<UInteractComponent>("InteractComp");

}

// Called when the game starts or when spawned
void AInteractuador::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractuador::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    CameraComp = FindComponentByClass<UCameraComponent>();
}

// Called every frame
void AInteractuador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInteractuador::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    PlayerInputComponent->BindAxis("MoverAdelante", this, &AInteractuador::MoverAdelante);
    PlayerInputComponent->BindAxis("MoverLados", this, &AInteractuador::MoverLados);
    //PlayerInputComponent->BindAxis("EjercerFuerza", this, &AMG_Interactuador::EjercerFuerza);

    PlayerInputComponent->BindAxis("Girar", this, &AInteractuador::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Mirar", this, &AInteractuador::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Pick", IE_Pressed, this, &AInteractuador::PickObject);

}

void AInteractuador::MoverAdelante(float Val)
{
    if (Val != 0.f)
    {
        if (Controller)
        {
            FRotator const ControlSpaceRot = Controller->GetControlRotation();

            // transform to world space and add it
            AddMovementInput(ControlSpaceRot.Vector(), Val); //FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
        }
    }
}

void AInteractuador::MoverLados(float Val)
{
    if (Val != 0.f)
    {
        if (Controller)
        {
            FRotator const ControlSpaceRot = Controller->GetControlRotation();

            // transform to world space and add it
            AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
        }
    }
}

FVector AInteractuador::GetPawnViewLocation() const
{
    return CameraComp->GetComponentLocation();
}

void AInteractuador::PickObject()
{
    InteractComp->ApplyImpulse();
}

