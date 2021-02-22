// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "InteractiveActor.h"
#include "InteractiveProp.generated.h"

UCLASS()
class TURRETSYNDROME_API AInteractiveProp : public AActor, public IInteractiveActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
		int InteractionCount;
public:	
	// Sets default values for this actor's properties
	AInteractiveProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void Interact(APawn* Interactor);
	virtual void Interact_Implementation(APawn* Interactor) override;
};
