// Copyright Lee Chang Young 2019.

#include "OpenDoor.h"
#include <GameFramework/Actor.h>
#include "Grabber.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

void UOpenDoor::OpenTheDoor()
{
	//Owner->SetActorRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseTheDoor()
{
	//Owner->SetActorRelativeRotation(FRotator::ZeroRotator);
	OnCloseRequest.Broadcast();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the Trigger Volume
	//If the ActorThatOpens is in the volume
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate is not exist on %s"), *(Owner->GetName()));
	}
	else
	{
		if (GetTotalMassOfActorsOnPlate() > MassToOpenDoor)
		{
			OpenTheDoor();
		}
		else
		{
			CloseTheDoor();
		}
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	if (PressurePlate == nullptr)
	{
		return TotalMass;
	}
	else
	{
		TArray<AActor*> ActorsOnPlate = TArray<AActor*>();
		PressurePlate->GetOverlappingActors(/*out*/ActorsOnPlate);

		for (auto& ActorOnPlate : ActorsOnPlate)
		{
			TotalMass += ActorOnPlate->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}

		return TotalMass;
	}
	
}
