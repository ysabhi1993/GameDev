// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

private:
	float Reach = 100.0f;
	UPhysicsHandleComponent *Handler = nullptr;
	UInputComponent *InputComponent = nullptr;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	void Grab();
	void Release();
	FVector GetLineTraceEnd();
	FHitResult GetHitResult();
	
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};