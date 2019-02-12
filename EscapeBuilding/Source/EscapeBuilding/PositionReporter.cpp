// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "EscapeBuilding.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString object_name = GetOwner()->GetName();
	FVector object_pos = GetOwner()->GetActorTransform().GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("Position Reporter for %s"), *object_name);
	UE_LOG(LogTemp, Warning, TEXT("Position of %s is x=%f, y=%f, z=%f"), *object_name, object_pos.X, object_pos.Y, object_pos.Z);

	// ...
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

