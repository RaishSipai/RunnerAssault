// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseLevel.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Constants for configuration
constexpr float DefaultIterativeNextArrowLocation = 5000.0f;
constexpr float IterativeNextArrowIncrement = 1000.0f;
constexpr float LifespanAfterOverlap = 15.0f;

// Sets default values
ABaseLevel::ABaseLevel()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize components
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyScene"));
	RootComponent = MyScene;

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

	// Set initial arrow location
	IterativeNextArrowLocation = DefaultIterativeNextArrowLocation;
	NextSpawnLocationArrow->SetWorldLocation(FVector(0.0f, IterativeNextArrowLocation, 0.0f));

	bIsStairUp = false;
	bIsStairDown = false;
}

// Called when the game starts or when spawned
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();

	// Bind the overlap event
	Checkpoint->OnComponentBeginOverlap.AddDynamic(this, &ABaseLevel::OnOverlapBegin);

	// Spawn initial obstacle
	SpawnObstacle();
}

// Spawns an obstacle at one of the three lanes
void ABaseLevel::SpawnObstacle()
{
	if (ObstacleClass)
	{
		float RandomNumber = FMath::FRandRange(0.0f, 3.0f);
		FVector TempSpawnLocation;

		if (RandomNumber <= 1.0f)
		{
			TempSpawnLocation = RightArrow->GetComponentLocation();
			SpawnGoldCoin("RightArrow");
		}
		else if (RandomNumber <= 2.0f)
		{
			TempSpawnLocation = MiddleArrow->GetComponentLocation();
			SpawnGoldCoin("MiddleArrow");
		}
		else
		{
			TempSpawnLocation = LeftArrow->GetComponentLocation();
			SpawnGoldCoin("LeftArrow");
		}

		GetWorld()->SpawnActor(ObstacleClass, &TempSpawnLocation, &FRotator::ZeroRotator);
	}
}

// Spawns the next level or chunk
void ABaseLevel::SpawnLevel()
{
	if (ChunkClass && UpStairClass && DownStairClass)
	{
		FVector TempSpawnLocation = NextSpawnLocationArrow->GetComponentLocation();
		IterativeNextArrowLocation += IterativeNextArrowIncrement;
		NextSpawnLocationArrow->SetWorldLocation(FVector(0.0f, IterativeNextArrowLocation, 0.0f));

		float RandomNumber = FMath::FRandRange(1.0f, 3.0f);

		if (RandomNumber <= 1.5f)
		{
			bIsStairUp = false;
			bIsStairDown = false;
			GetWorld()->SpawnActor(ChunkClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
		else if (RandomNumber <= 2.0f)
		{
			if (RandomNumber <= 1.75f && !bIsStairDown)
			{
				bIsStairUp = true;
				GetWorld()->SpawnActor(UpStairClass, &TempSpawnLocation, &FRotator::ZeroRotator);
			}
			else if (RandomNumber <= 2.0f && !bIsStairUp)
			{
				bIsStairDown = true;
				GetWorld()->SpawnActor(DownStairClass, &TempSpawnLocation, &FRotator::ZeroRotator);
			}
			else
			{
				GetWorld()->SpawnActor(ChunkClass, &TempSpawnLocation, &FRotator::ZeroRotator);
			}
		}
		else
		{
			GetWorld()->SpawnActor(ChunkClass, &TempSpawnLocation, &FRotator::ZeroRotator);
		}
	}
}

// Spawns a gold coin at the specified arrow location
void ABaseLevel::SpawnGoldCoin(FName ArrowName)
{
	if (CoinClass)
	{
		FVector TempSpawnLocation;

		if (ArrowName == "RightArrow")
		{
			TempSpawnLocation = FMath::RandBool() ? MiddleArrow->GetComponentLocation() : LeftArrow->GetComponentLocation();
		}
		else if (ArrowName == "MiddleArrow")
		{
			TempSpawnLocation = FMath::RandBool() ? RightArrow->GetComponentLocation() : LeftArrow->GetComponentLocation();
		}
		else if (ArrowName == "LeftArrow")
		{
			TempSpawnLocation = FMath::RandBool() ? RightArrow->GetComponentLocation() : MiddleArrow->GetComponentLocation();
		}

		GetWorld()->SpawnActor(CoinClass, &TempSpawnLocation, &FRotator::ZeroRotator);
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
		// Destroys itself when object spawned within 15 seconds
		SetLifeSpan(LifespanAfterOverlap);
		SpawnLevel();
	}
}
