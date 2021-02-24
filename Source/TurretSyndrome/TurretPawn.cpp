// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h" 
#include "TurretTorsoActor.h"
#include "TurretHeadActor.h"
#include "TurretSyndrome.h" // For LogTurret.


// Sets default values
ATurretPawn::ATurretPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PitchMin = -20.0f;
	PitchMax = 20.0f;
	FovMin = 50.0f;
	FovMax = 70.0f;

	Shooting = false;
	Pilot = nullptr;

	TorsoActorClass = nullptr;
	HeadActorClass = nullptr;

	FeetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	FeetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	FeetComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	RootComponent = FeetComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(FeetComponent);

	HipComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Hip"));
	HipComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	HipComponent->SetupAttachment(FeetComponent);

	NeckComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Neck"));
	NeckComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	NeckComponent->SetRelativeRotation(FRotator((PitchMin + PitchMax) * 0.5f, 0.0f, 0.0f));
	NeckComponent->SetupAttachment(HipComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(10.0f, 0.0f, 10.0f));
	CameraComponent->SetupAttachment(NeckComponent);
	CameraComponent->FieldOfView = (FovMin + FovMax) * 0.5f;
}

void ATurretPawn::DeSpawnTorso() {
	if (!TorsoActor)
		return;
	TorsoActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	TorsoActor->InteractiveTurret = nullptr;
	TorsoActor->Destroy();
	TorsoActor = nullptr;
}

void ATurretPawn::SpawnTorso() {
	if (!TorsoActorClass)
		return;
	if (TorsoActor)
		DeSpawnTorso();
	FActorSpawnParameters SpawnParams;
	TorsoActor = GetWorld()->SpawnActor<ATurretTorsoActor>(TorsoActorClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
	NeckComponent->SetRelativeLocation(TorsoActor->NeckLocationComponent->GetRelativeLocation());
	NeckComponent->SetRelativeRotation(TorsoActor->NeckLocationComponent->GetRelativeRotation());
	TorsoActor->AttachToComponent(HipComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	TorsoActor->InteractiveTurret = this;
}

void ATurretPawn::DeSpawnHead() {
	if (!HeadActor)
		return;
	HeadActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	HeadActor->InteractiveTurret = nullptr;
	HeadActor->Destroy();
	HeadActor = nullptr;
}

void ATurretPawn::SpawnHead() {
	if (!HeadActorClass)
		return;
	if (HeadActor)
		DeSpawnHead();
	FActorSpawnParameters SpawnParams;
	HeadActor = GetWorld()->SpawnActor<ATurretHeadActor>(HeadActorClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
	CameraComponent->SetRelativeLocation(HeadActor->CameraLocationComponent->GetRelativeLocation());
	CameraComponent->SetRelativeRotation(HeadActor->CameraLocationComponent->GetRelativeRotation());
	HeadActor->AttachToComponent(NeckComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	HeadActor->InteractiveTurret = this;
}



// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	SpawnTorso();
	SpawnHead();
	Super::BeginPlay();
}


// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Shooting) {
		if (HeadActor) {
			HeadActor->TryToFire();
		}
	}
}

// Called to bind functionality to input
void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("TurretYaw", this, &ATurretPawn::YawRot);
	InputComponent->BindAxis("TurretPitch", this, &ATurretPawn::PitchRot);
	InputComponent->BindAxis("TurretZoom", this, &ATurretPawn::Zoom);
	InputComponent->BindAction("TurretExit", IE_Pressed, this, &ATurretPawn::ExitTurret);
	InputComponent->BindAction("TurretShoot", IE_Pressed, this, &ATurretPawn::StartShooting);
	InputComponent->BindAction("TurretShoot", IE_Released, this, &ATurretPawn::StopShooting);
}

void ATurretPawn::YawRot(float value)
{
	if (value) {
		HipComponent->AddLocalRotation(FRotator(0.0f, value, 0.0f));
	}
}

void ATurretPawn::PitchRot(float value)
{
	if (value) {
		float new_pitch = NeckComponent->GetRelativeRotation().Pitch + value;
		new_pitch = new_pitch < PitchMin ? PitchMin : new_pitch < PitchMax ? new_pitch : PitchMax;
		NeckComponent->SetRelativeRotation(FRotator(new_pitch, 0.0f, 0.0f));
	}
}

void ATurretPawn::Zoom(float value)
{
	if (value) {
		float new_fov = CameraComponent->FieldOfView + value;
		new_fov = new_fov < FovMin ? FovMin : new_fov < FovMax ? new_fov : FovMax;
		CameraComponent->FieldOfView = new_fov;
	}
}

bool ATurretPawn::SetPilot(APawn* pilot, bool Force) {
	UE_LOG(LogTurret, Display, TEXT("Turret %s, current pilot is %s, new pilot is %s"),
		*GetNameSafe(this), *GetNameSafe(Pilot), *GetNameSafe(pilot)
	);
	if (pilot == Pilot) {
		UE_LOG(LogTurret, Display, TEXT("Pilot is not changed, nothing more to do"));
		return false;
	}

	if (Pilot) {
		if (!Force) {
			UE_LOG(LogTurret, Warning, TEXT("Turret will not eject pilot because it is not forced"));
			return false;
		}
		// Send the current pilot back to its body.
		AController* controller = GetController();
		if (Controller) {
			controller->UnPossess();
			controller->Possess(Pilot);
			UE_LOG(LogTurret, Display, TEXT("Current pilot ejected"));
		}
		else {
			UE_LOG(LogTurret, Error, TEXT("Turret has a pilot but no controller, which should not happen. Nulling pilot."));
		}
		Shooting = false;
		Pilot = nullptr;
	}

	// Assign the new pilot, if there is one.
	if (!pilot) {
		UE_LOG(LogTurret, Display, TEXT("New pilot is nullptr, nothing more to do"));
		return false;
	}

	AController* controller = pilot->GetController();
	if (controller) {
		controller->UnPossess();
		controller->Possess(this);
		UE_LOG(LogTurret, Display, TEXT("New pilot assigned"));
		Pilot = pilot;
		return true;
	}
	else {
		UE_LOG(LogTurret, Error, TEXT("Cannot assign a pilot that has no controller."));
		return false;
	}
}


void ATurretPawn::ExitTurret() {
	UE_LOG(LogTurret, Display, TEXT("Exiting Turret %s"), *GetNameSafe(this));
	SetPilot(nullptr, true);
}

void ATurretPawn::StartShooting() {
	Shooting = true;
}

void ATurretPawn::StopShooting() {
	Shooting = false;
}

void ATurretPawn::Interact_Implementation(APawn* Interactor) {
	UE_LOG(LogTurret, Display, TEXT("Interacted with Turret %s"), *GetNameSafe(this));
	SetPilot(Interactor, false);
}
