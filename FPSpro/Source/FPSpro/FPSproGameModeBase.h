// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSproGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSPRO_API AFPSproGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		virtual void StartPlay() override;
};
