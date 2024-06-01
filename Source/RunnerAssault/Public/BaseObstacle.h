// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "BaseObstacle.generated.h"

class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class RUNNERASSAULT_API ABaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObstacle();

	/** Default Scene Component that become RootComponent of this Actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	USceneComponent* MyObstacleScene;

	/** HitBox when character collides with it dies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkpoints)
	UBoxComponent* HitBox;

	/** Obstacle Mesh to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Checkpoints)
	UStaticMeshComponent* ObstacleMesh;

	// handles how many time game is paused
	FTimerHandle TimerHandle_PauseGame;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Game")
	TSubclassOf<UUserWidget> GameOverMenu;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;

	// Function that removes all currently active UserWidget in viewport
	void RemoveAllCurrentActiveWidget() const;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	void ChangeMenuWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to pause a game
	void PauseGame();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
