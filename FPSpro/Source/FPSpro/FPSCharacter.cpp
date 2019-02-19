// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ����һ�˳�����������
	FPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// �������������ӵ������������
	FPSCameraComp->SetupAttachment(GetCapsuleComponent());

	// ��������������۾��Ϸ���Զ����
	FPSCameraComp->SetRelativeLocation(FVector(-100.0f, 0.0f, 50.0f + BaseEyeHeight));
	// �� pawn �����������ת��
	FPSCameraComp->bUsePawnControlRotation = true;

	// Ϊӵ����Ҵ���һ����һ�˳�ģ�������
	FPSMesh  = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//���ø�ģ�ͽ���ӵ�е���ҿɼ�
	FPSMesh->SetOnlyOwnerSee(true);
	//������ӵ������
	FPSMesh->SetupAttachment(FPSCameraComp);
	//ȥ����Ӱ
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// ��ʾ������Ϣ���롣-1������ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCharacter::MoveForward(float Value)
{
	// ��ȷ�ĸ������ǡ�ǰ����������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// ��ȷ�ĸ������ǡ����ҡ�������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

//��value��ֵ��������������Ϊ��������ȵĵ���
void AFPSCharacter::FormatAix(float Value) {
	AFPSCharacter::AddControllerYawInput(Value * 0.5);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ���á��ƶ����󶨡�
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	// ���á��鿴���󶨡�
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::FormatAix);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// ���á��������󶨡�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

