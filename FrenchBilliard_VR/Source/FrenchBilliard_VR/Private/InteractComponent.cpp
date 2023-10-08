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

bool UInteractComponent::BeginDrag()
{
	AActor* MyOwner = GetOwner();

	FVector LocalPos;
	FQuat4d LocalRot;
	//UPhysicsHandleComponent* PhysHandleComp = GetPhysicsHandleComp(MyOwner);

	//if (!PhysHandleComp)
	//{
	//	return false;
	//}

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End(EyeLocation + (EyeRotation.Vector() * 500.0f));

	//FHitResult Hit;
	//bool bBlocking = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	//FHitResult Hit;	
	//bool bBlocking = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	
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
			End = Hit.ImpactPoint;
	
			//OnGrabObject.Broadcast(nullptr, Hit.GetComponent(), Hit.ImpactPoint);
	
			//LocalRot = MyOwner->GetTransform().InverseTransformRotation(Hit.GetActor()->GetActorRotation().Quaternion());
			//LocalPos = MyOwner->GetTransform().InverseTransformPosition(Hit.ImpactPoint);
	
			//PhysHandleComp->GrabComponentAtLocationWithRotation(Hit.GetComponent(),
			//	Hit.BoneName,
			//	Hit.ImpactPoint,
			//	Hit.GetActor()->GetActorRotation());
			//
	
			//if (AMG_TuboSkeleton* tt = Cast<AMG_TuboSkeleton>(HitActor))
			//{
			//	tt->InsertTubo(5.0f);
			//}
	
			//break;
		}
	}

	//Radius = 3.0f;
	DrawDebugSphere(GetWorld(), End, Radius, 32, LineColor, false, 0.0f);
	//DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 0.0f);

	//PossesObject = bBlocking;

	return bBlocking;
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

