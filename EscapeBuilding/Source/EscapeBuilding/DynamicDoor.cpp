// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UDynamicDoor::UDynamicDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDynamicDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	doorOwner = GetOwner();
}

void UDynamicDoor::OpenDoor()
{
	doorOwner->SetActorRotation(FRotator(0.0f, 150.0f, 0.0f));
}

void UDynamicDoor::CloseDoor() {
	
	doorOwner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}

// Called every frame
void UDynamicDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}