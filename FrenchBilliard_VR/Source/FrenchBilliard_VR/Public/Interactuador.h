// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactuador.generated.h"

class UInteractComponent;
class UCameraComponent;

UCLASS()
class FRENCHBILLIARD_VR_API AInteractuador : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInteractuador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
	UInteractComponent* InteractComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	// Input functions
	void MoverAdelante(float Val);
	void MoverLados(float Val);

	void PickObject();
};
