// Copyright Lee Chang Young 2019.

#include "OpenDoor.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>


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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenTheDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.0f, -90.0f, 0.0f);

	Owner->SetActorRelativeRotation(NewRotation);
}

void UOpenDoor::CloseTheDoor()
{
	AActor* Owner = GetOwner();

	Owner->SetActorRelativeRotation(FRotator::ZeroRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the Trigger Volume
	//If the ActorThatOpens is in the volume
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate is not exist on %s"), *(GetOwner()->GetName()));
	}
	else
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			OpenTheDoor();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
		else if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		{
			CloseTheDoor();
		}
	}
}

