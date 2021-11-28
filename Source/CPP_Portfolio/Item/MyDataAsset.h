// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PORTFOLIO_API UMyDataAsset : public UDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCItemAsset> item;
};