// Fill out your copyright notice in the Description page of Project Settings.


#include "Startinglevel.h"
#include "Components/SceneComponent.h"

// Sets default values
AStartinglevel::AStartinglevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize components
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	RootComponent = MyScene;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AStartinglevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartinglevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
