// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Engine.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个第一人称摄像机组件。
	FPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// 将摄像机组件附加到胶囊体组件。
	FPSCameraComp->SetupAttachment(GetCapsuleComponent());

	// 将摄像机放置在眼睛上方不远处。
	FPSCameraComp->SetRelativeLocation(FVector(-100.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 用 pawn 控制摄像机旋转。
	FPSCameraComp->bUsePawnControlRotation = true;

	// 为拥有玩家创建一个第一人称模型组件。
	FPSMesh  = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//设置该模型仅对拥有的玩家可见
	FPSMesh->SetOnlyOwnerSee(true);
	//将手添加到摄像机
	FPSMesh->SetupAttachment(FPSCameraComp);
	//去除阴影
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
		// 显示调试信息五秒。-1“键”值（首个参数）说明我们无需更新或刷新此消息。
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
	// 明确哪个方向是“前进”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// 明确哪个方向是“向右”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

//对value的值进行修正，假设为鼠标灵敏度的调整
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
	// 设置“移动”绑定。
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	// 设置“查看”绑定。
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::FormatAix);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// 设置“动作”绑定。
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

