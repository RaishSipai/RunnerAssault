// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevel.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

#include "Location.h"

// Sets default values
ABaseLevel::ABaseLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	RootComponent = MyScene;

	// floor mesh to be spawned initializing
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(RootComponent);
	Checkpoint = CreateDefaultSubobject<UBoxComponent>(TEXT("Checkpoint"));
	Checkpoint->SetupAttachment(RootComponent);

	NextSpawnLocationArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("NextSpawnLocationArrow"));
	NextSpawnLocationArrow->SetupAttachment(RootComponent);

	RightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrow"));
	RightArrow->SetupAttachment(RootComponent);

	MiddleArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleArrow"));
	MiddleArrow->SetupAttachment(RootComponent);

	LeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrow"));
	LeftArrow->SetupAttachment(RootComponent);

	IterativeNextArrowLocation = 5000.0f;
	NextSpawnLocationArrow->SetWorldLocation(FVector(0.0f, IterativeNextArrowLocation, 0.0f));

}

// Called when the game starts or when spawned
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();

	// Bind the overlap event
	Checkpoint->OnComponentBeginOverlap.AddDynamic(this, &ABaseLevel::OnOverlapBegin);

	SpawnObstacle();
	
}

void ABaseLevel::SpawnObstacle()
{
	// Checks if ObstacleClass is not null and spawn obstacle at any three lanes
	if (ObstacleClass)
	{
		float RandomNumber = FMath::FRandRange(0.0f, 3.0f); // Gives random float value between 1.0 to 3.0
		if (RandomNumber <= 1.0f)
		{
			FVector TempSpawnLocation = RightArrow->GetComponentLocation();
			GetWorld()->SpawnActor(ObstacleClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
		else if (RandomNumber <= 2.0f)
		{
			FVector TempSpawnLocation = MiddleArrow->GetComponentLocation();
			GetWorld()->SpawnActor(ObstacleClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
		else if (RandomNumber <= 3.0f)
		{
			FVector TempSpawnLocation = LeftArrow->GetComponentLocation();
			GetWorld()->SpawnActor(ObstacleClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
	}
}

void ABaseLevel::SpawnLevel()
{
	// Checks if ObstacleClass is not null and spawn obstacle at any three lanes
	if (ChunkClass)
	{
		FVector TempSpawnLocation = NextSpawnLocationArrow->GetComponentLocation();
		IterativeNextArrowLocation += 1000.0f;
		NextSpawnLocationArrow->SetWorldLocation(FVector(0.0f, IterativeNextArrowLocation, 0.0f));

		float RandomNumber = FMath::FRandRange(0.0f, 2.0f); // Gives random float value between 1.0 to 3.0
		if (RandomNumber <= 1.5f)
		{
			GetWorld()->SpawnActor(ChunkClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
		else if (RandomNumber <= 2.0f)
		{
			if (RandomNumber <= 1.75f)
			{
				GetWorld()->SpawnActor(UpStairClass, &TempSpawnLocation, &FRotator::ZeroRotator);
			}
			else
			{
				GetWorld()->SpawnActor(DownStairClass, &TempSpawnLocation, &FRotator::ZeroRotator);
			}
		}
	}
}

// Called every frame
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		// Destroys itself when object spawned within 10 seconds
		SetLifeSpan(15.0f);
		SpawnLevel();
	}
}

