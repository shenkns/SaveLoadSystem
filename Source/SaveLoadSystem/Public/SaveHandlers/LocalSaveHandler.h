// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "SaveHandlers/SaveHandler.h"

#include "LocalSaveHandler.generated.h"

UCLASS()
class SAVELOADSYSTEM_API ULocalSaveHandler : public USaveHandler
{
	GENERATED_BODY()

public:

	virtual bool SaveProfileStats(TArray<UStat*> Stats) override;
	virtual TArray<UStat*> LoadProfileStats() override;
};
