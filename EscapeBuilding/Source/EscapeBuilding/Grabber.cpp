// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*
 * This method tells when to Grab an actor
 */
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab called"));

	auto HitResult = GetHitResult();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit) {
		Handler->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release called"))
}

FVector UGrabber::GetLineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//Generates a line pointing at the view point
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return LineEnd;
}

/*
 * This method gets the Body that is hit by the player
 * Sets the Line trace on the player to the body the player hits
 * Marks a point at the end of the traced line
 */
FHitResult UGrabber::GetHitResult()
{
	FColor WhiteColor = FColor(255, 255, 255);
	FColor RedColor = FColor(255, 0, 0);
	FColor BlackColor = FColor(0, 0, 0);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	FVector LineEnd = GetLineTraceEnd();
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	DrawDebugPoint(GetWorld(), LineEnd, 3.0f, WhiteColor, false, 0.0f, 0.0f);
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
	
	return Hit;
}



// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Handler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Handler->GetGrabbedComponent()) {
		Handler->SetTargetLocation(GetLineTraceEnd());
	}
	
}
