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

	//ǰ����ƶ�
	UFUNCTION()
		void MoveForward(float value);

	//���ҵ��ƶ�
	UFUNCTION()
		void MoveRight(float value);

	//�������������
	UFUNCTION()
		void FormatAix(float value);
	//��Ծ
	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

	// FPS �������
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComp;

	// ��һ�˳�ģ�ͣ��ֱۣ�������ӵ����ҿɼ���
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};