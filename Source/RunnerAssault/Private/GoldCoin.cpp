// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldCoin.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AGoldCoin::AGoldCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyGoldCoinScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyObstacleScene"));
	RootComponent = MyGoldCoinScene;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	CoinMesh->SetupAttachment(RootComponent);

	// Initialize rotation speed (degrees per second)
	RotationSpeed = 90.0f;

}

// Called when the game starts or when spawned
void AGoldCoin::BeginPlay()
{
	Super::BeginPlay();
	
	// Destroys itself when object spawned within 10 seconds
	SetLifeSpan(14.0f);

	// Bind the overlap event
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AGoldCoin::OnOverlapBegin);
}

// Called every frame
void AGoldCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate rotation for this frame
	FRotator Rotation = FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f);

	// Apply rotation to the actor
	AddActorLocalRotation(Rotation);

}

void AGoldCoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		Destroy();
	}
}

