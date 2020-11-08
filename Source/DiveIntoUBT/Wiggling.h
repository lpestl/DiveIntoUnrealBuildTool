// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wiggling.generated.h"

UCLASS()
class DIVEINTOUBT_API AWiggling : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWiggling();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WigglingMultiplier = 10.0f;
private:
	float CurrentTime = 0.0f;
};
