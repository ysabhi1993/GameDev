// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DynamicDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UDynamicDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDynamicDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;
		
};
