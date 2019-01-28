// Copyright Lee Chang Young 2019.

#include "Grabber.h"
#include <GameFramework/Actor.h>
#include <Components/ActorComponent.h>
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
#include <CollisionQueryParams.h>
#include <Engine/Engine.h>
#include <Components/PrimitiveComponent.h>

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	FindInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached move along the physics handle
	if (PhysicsHandle != nullptr && PhysicsHandle->GrabbedComponent != nullptr)
	{
		FVector LineStart, LineEnd;
		GetLineStartAndEnd(LineStart, LineEnd);
		PhysicsHandle->SetTargetLocation(LineEnd);
	}
}

void UGrabber::FindPhysicsHandle()
{
	//PhysicsHandle = GetOwner()->FindComponentByClass(UPhysicsHandleComponent::StaticClass());
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ther is no PhysicsHandle on %s"), *GetOwner()->GetName()));
	}
}

void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ther is no InputComponent on %s"), *GetOwner()->GetName()));
	}
}


void UGrabber::Grab()
{
	// Line trace and see if we reach any actor  Try and Reach and actors with physics body collision channel set
	UPrimitiveComponent* ComponentToGrab = GetFirstPhysicsBodyInReach().GetComponent();

	if (ComponentToGrab != nullptr && PhysicsHandle != nullptr)
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab,
											   NAME_None, // no bones needed
											   ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle != nullptr && PhysicsHandle->GrabbedComponent != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::GetLineStartAndEnd(FVector& LineStart, FVector& LineEnd) const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(/*out*/ PlayerViewPointLocation, /*out*/ PlayerViewPointRotation);

	LineStart = PlayerViewPointLocation;
	LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector LineStart, LineEnd;
	GetLineStartAndEnd(LineStart, LineEnd);
	//Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(/*out*/HitResult,
											LineStart,
											LineEnd,
											FCollisionObjectQueryParams(ECC_PhysicsBody),
											TraceParameters);
	return HitResult;
}