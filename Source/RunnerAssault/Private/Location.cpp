// Fill out your copyright notice in the Description page of Project Settings.


#include "Location.h"

// Sets default values
ALocation::ALocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ALocation::SetLocation(FVector Xyz)
{
	SetActorLocation(Xyz);
}

void ALocation::SetRotation(FRotator Xyz)
{
	SetActorRotation(Xyz);
}

// Called when the game starts or when spawned
void ALocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

