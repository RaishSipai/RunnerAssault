// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldCoin.generated.h"

class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class RUNNERASSAULT_API AGoldCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoldCoin();

	/** Default Scene Component that become RootComponent of this Actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	USceneComponent* MyGoldCoinScene;

	/** HitBox when character collides with it dies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkpoints)
	UBoxComponent* HitBox;

	/** Obstacle Mesh to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoinProperties)
	UStaticMeshComponent* CoinMesh;

	// Rotation speed (degrees per second)
	UPROPERTY(EditAnywhere, Category = CoinProperties)
	float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
