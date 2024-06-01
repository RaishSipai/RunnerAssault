// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EndlessRunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/GameViewportClient.h"
#include "Engine/LocalPlayer.h"

// Sets default values
ABaseObstacle::ABaseObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyObstacleScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyObstacleScene"));
	RootComponent = MyObstacleScene;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseObstacle::BeginPlay()
{
	Super::BeginPlay();

	// Destroys itself when object spawned within 10 seconds
	SetLifeSpan(14.0f);

	// Bind the overlap event
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseObstacle::OnOverlapBegin);
	
}

void ABaseObstacle::RemoveAllCurrentActiveWidget() const
{
	ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (LocalPlayer)
	{
		UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
		if (ViewportClient)
		{
			ViewportClient->RemoveAllViewportWidgets();
		}
	}
}

void ABaseObstacle::ChangeMenuWidget()
{
	RemoveAllCurrentActiveWidget();
	if (GameOverMenu != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverMenu);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

// Called every frame
void ABaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseObstacle::PauseGame()
{
	// Pause the game
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ABaseObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		AEndlessRunnerCharacter* RunnerCharacter = Cast<AEndlessRunnerCharacter>(OtherActor);
		if (RunnerCharacter)
		{
			ChangeMenuWidget();
			RunnerCharacter->bIsDead = true;
			//Pause the game after 5 seconds
			GetWorldTimerManager().SetTimer(TimerHandle_PauseGame, this, &ABaseObstacle::PauseGame, 5.0f, false);
		}
	}
}

