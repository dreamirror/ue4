// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.generated.h"
UCLASS()
class FPSPRO_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//前后的移动
	UFUNCTION()
		void MoveForward(float value);

	//左右的移动
	UFUNCTION()
		void MoveRight(float value);

	//鼠标灵敏度修正
	UFUNCTION()
		void FormatAix(float value);
	//跳跃
	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

	// FPS 摄像机。
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComp;

	// 第一人称模型（手臂），仅对拥有玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};
