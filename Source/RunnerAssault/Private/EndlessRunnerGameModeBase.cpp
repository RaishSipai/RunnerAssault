// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameModeBase.h"
#include "EndlessRunnerCharacter.h"
#include "Engine/GameViewportClient.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/LocalPlayer.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBpClass(TEXT("/Game/EndlessRunner/Blueprints/BP_EndlessRunnerCharacter"));
    if (PlayerPawnBpClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBpClass.Class;
    }
}

void AEndlessRunnerGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    RemoveAllCurrentActiveWidget();
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void AEndlessRunnerGameModeBase::RemoveAllCurrentActiveWidget() const
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

void AEndlessRunnerGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

