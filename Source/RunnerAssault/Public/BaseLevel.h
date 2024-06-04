// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevel.generated.h"

class UBoxComponent;
class UArrowComponent;
class USceneComponent;

UCLASS()
class RUNNERASSAULT_API ABaseLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLevel();

	/** Default Scene Component that become RootComponent of this Actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	USceneComponent* MyScene;

	/** Arrow Component that stores next mesh spawn location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arrow)
	UArrowComponent* NextSpawnLocationArrow;

	/** Arrow Component that stores right side lane location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arrow)
	UArrowComponent* RightArrow;

	/** Arrow Component that stores middle side lane location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arrow)
	UArrowComponent* MiddleArrow;

	/** Arrow Component that stores left side lane location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arrow)
	UArrowComponent* LeftArrow;

	/** Mesh Floor To be Spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = floor)
	class UStaticMeshComponent* FloorMesh;

	/** Checkpoint when character hits up new floor spawns */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkpoints)
	UBoxComponent* Checkpoint;

	/** A Next Level that to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunks)
	TSubclassOf<AActor> ChunkClass;

	/** A Next Level that to be spawned upStairs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunks)
	TSubclassOf<AActor> UpStairClass;

	/** A Next Level that to be spawned downStairs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunks)
	TSubclassOf<AActor> DownStairClass;

	/** A Obstacle class that contains many meshes act as obstacle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunks)
	TSubclassOf<AActor> ObstacleClass;

	/** Iterative variable that updates arrow spawn location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChunkLocation)
	float IterativeNextArrowLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// To spawn obstacle at any of 3 lanes
	void SpawnObstacle();

	// Called to spawn next level or floor or chunk class when character reached at checkpoint
	void SpawnLevel();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
