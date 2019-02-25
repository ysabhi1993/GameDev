// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

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
	doorOwner = GetOwner();
}

// Called every frame
void UDynamicDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetActorsWeightOnPressurePlate() > WeightNeededToOpen) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

void UDynamicDoor::OpenDoor()
{
	if (!doorOwner) { 
		UE_LOG(LogTemp, Error, TEXT("Could not find Door Owner"))
		return; 
	}
	doorOwner->SetActorRotation(FRotator(0.0f, 150.0f, 0.0f));
}

void UDynamicDoor::CloseDoor()
{
	if (!doorOwner) { 
		UE_LOG(LogTemp, Error, TEXT("Could not find Door Owner"))
		return; 
	}
	doorOwner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}

float UDynamicDoor::GetActorsWeightOnPressurePlate()
{
	if (!PressurePlate) { 
		UE_LOG(LogTemp, Error, TEXT("Could not find Pressure Plate"))
		return 200.0f; 
	}
	float TotalMass = 0.f;
	TArray<AActor *> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto * Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}