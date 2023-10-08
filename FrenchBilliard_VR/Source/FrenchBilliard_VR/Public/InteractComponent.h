// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRENCHBILLIARD_VR_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

	bool BeginDrag();

	void ApplyImpulse();
	//UFUNCTION(BlueprintCallable, Category = "PhysicsComp")
	//static UPhysicsHandleComponent* GetPhysicsHandleComp(AActor* FromActor);

	UPROPERTY(EditAnywhere)
	float ImpulseMagnitud = 10.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool CastObjects(FHitResult* HitResult, FVector& Direction);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
