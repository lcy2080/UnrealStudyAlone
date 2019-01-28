// Copyright Lee Chang Young 2019.

#pragma once

#include <Engine/TriggerVolume.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALSTUDYALONE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenTheDoor();
	void CloseTheDoor();


	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	AActor* Owner;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OpenDoor")
	float openAngle = -60.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OpenDoor")
	float MassToOpenDoor = 50.f;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
};
