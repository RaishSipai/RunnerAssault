// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Startinglevel.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class RUNNERASSAULT_API AStartinglevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartinglevel();

	/** Default Scene Component that becomes RootComponent of this Actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	USceneComponent* MyScene;

	/** Mesh Floor To be Spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor)
	class UStaticMeshComponent* FloorMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
