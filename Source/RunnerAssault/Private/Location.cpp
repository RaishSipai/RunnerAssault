// Fill out your copyright notice in the Description page of Project Settings.


#include "Location.h"
#include "TimerManager.h"

// Sets default values
ALocation::ALocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ConsideredForwardVector = FVector(0.0f, 1.0f, 0.0f);
	ConsiderdForwardRotator = FRotator::ZeroRotator;

	bIsStairUsed = false;
}

void ALocation::SetLocation(FVector Xyz)
{
	SetActorLocation(Xyz);
}

void ALocation::SetRotation(FRotator Xyz)
{
	SetActorRotation(Xyz);
}

FVector ALocation::GetLocationCoordinates() const
{
	return GetActorLocation();
}

FRotator ALocation::GetLocationActorRotation() const
{
	return GetActorRotation();
}

// Called when the game starts or when spawned
void ALocation::BeginPlay()
{
	Super::BeginPlay();
	
	// Set a timer to call OnTimerExpire function after 5 seconds
	GetWorld()->GetTimerManager().SetTimer(StairTimerHandle, this, &ALocation::BoolControlOnTimerExprire, 15.0f, true);
}

// Called every frame
void ALocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocation::BoolControlOnTimerExprire()
{
	bIsStairUsed = false;
}

