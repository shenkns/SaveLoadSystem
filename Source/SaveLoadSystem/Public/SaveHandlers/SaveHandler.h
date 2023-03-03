// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "UObject/Object.h"

#include "SaveHandler.generated.h"

class UManagersSystem;
class UStatsManager;
class UStat;

UCLASS(Abstract, BlueprintType, Blueprintable)
class SAVELOADSYSTEM_API USaveHandler : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, Category = "SaveLoadSystem|Save", meta = (CompactNodeTitle = "System"))
	UManagersSystem* GetManagersSystem() const;

	UFUNCTION(BlueprintPure, Category = "SaveLoadSystem|Save", meta = (CompactNodeTitle = "Manager"))
	UStatsManager* GetManager() const;

	// Save-Load System Functions
	UFUNCTION(BlueprintNativeEvent, Category = "SaveLoadSystem|Save")
	bool SaveProfile(const TArray<UStat*>& Stats);

	UFUNCTION(BlueprintNativeEvent, Category = "SaveLoadSystem|Save")
	bool LoadProfile(TArray<UStat*>& Stats);

	virtual bool SaveProfileStats(TArray<UStat*> Stats);
	virtual TArray<UStat*> LoadProfileStats();
};
