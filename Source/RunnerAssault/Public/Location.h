// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Location.generated.h"

UCLASS()
class RUNNERASSAULT_API ALocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocation();

	UFUNCTION()
	void SetLocation(FVector Xyz);

	UFUNCTION()
	void SetRotation(FRotator Xyz);

	FVector GetLocationCoordinates() const; 

	FRotator GetLocationActorRotation() const;

	FVector ConsideredForwardVector;

	FRotator ConsiderdForwardRotator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Used to Identify which don't spawn stair down next to stair up
	bool bIsStairUsed;
	FTimerHandle StairTimerHandle;

	// Called to control bool variable stair can be spawn or not
	UFUNCTION()
	void BoolControlOnTimerExprire();

	static FVector StaticLocationCoordinates;

};
