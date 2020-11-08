// Fill out your copyright notice in the Description page of Project Settings.


#include "Wiggling.h"

// Sets default values
AWiggling::AWiggling()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWiggling::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWiggling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime * WigglingMultiplier;
	AddActorLocalOffset(FVector(0.0f, 0.0f, FMath::Sin(CurrentTime)));
}

