// Copyright Lee Chang Young 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/InputComponent.h>
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALSTUDYALONE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void FindPhysicsHandle();
	void FindInputComponent();
	void Grab();
	void Release();

	void GetLineStartAndEnd(FVector& LineStart, FVector& LineEnd) const;

	//Return hit for first physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

private:
	/* ray reached distance. */
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;
};
