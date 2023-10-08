// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UInteractComponent::CastObjects(FHitResult* HitResult, FVector& Direction)
{
	AActor* MyOwner = GetOwner();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End(EyeLocation + (EyeRotation.Vector() * 500.0f));

	TArray<FHitResult> Hits;
	float Radius = 1.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	bool bBlocking = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlocking ? FColor::Green : FColor::Red;

	for (FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			Direction = EyeRotation.Vector();

			if (HitResult)
			{
				*HitResult = Hit;
			}
			
			End = Hit.ImpactPoint;
			break;
		}
	}

	DrawDebugSphere(GetWorld(), End, Radius, 32, LineColor, false, 0.0f);

	return bBlocking;
}

bool UInteractComponent::BeginDrag()
{
	FVector Direction;
	FHitResult HitResult;

	return CastObjects(nullptr, Direction);
}

void UInteractComponent::ApplyImpulse()
{
	FVector Direction;
	FHitResult HitResult;

	if (CastObjects(&HitResult, Direction))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		HitComp->AddImpulseAtLocation(Direction * ImpulseMagnitud, HitResult.ImpactPoint);
	}
}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	BeginDrag();
	// ...
}

