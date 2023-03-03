// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "GameFramework/SaveGame.h"

#include "Libs/SerializationSystemLibrary.h"

#include "StatsSaveGame.generated.h"

UCLASS()
class SAVELOADSYSTEM_API UProfileSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	// Profile Data
	UPROPERTY()
	TArray<FObjectSaveData> ProfileStatsSaveData;

	UPROPERTY()
	int ProfileVersion;
};
