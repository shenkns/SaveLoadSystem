// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "Managers/Manager.h"

#include "Stats/Stat.h"
#include "StatsManager.generated.h"

class USaveHandler;

UCLASS()
class SAVELOADSYSTEM_API UStatsManager : public UManager
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	USaveHandler* SaveHandler;

	UPROPERTY()
	TArray<UStat*> Stats;

	UPROPERTY()
	int Version;

public:

	virtual void InitManager() override;

	// Stats Getters
	UFUNCTION(BlueprintPure, Category = "Profile|Stats", meta = (CompactNodeTitle = "Version"))
	int GetProfileStatsVersion() const { return Version; };

	UFUNCTION(BlueprintPure, Category = "Profile|Stats", meta = (CompactNodeTitle = "Stat", DeterminesOutputType = "Class"))
	UStat* GetStat(TSubclassOf<UStat> Class) const;
	
	template<typename T>
	T* GetStat() const;

	// Serialization
	UFUNCTION(BlueprintCallable, Category = "Profile|Stats", meta = (CompactNodeTitle = "Save"))
	bool SaveStats();

private:

	void InitSaveHandler();
	void InitStats();
	void LoadProfileStats();
	void CreateNewProfileStats();
};

template <typename T>
T* UStatsManager::GetStat() const
{
	// Find Stat
	UStat* const* Out = Stats.FindByPredicate([&](const UStat* Src)
	{
		return Src && Src->GetClass() == T::StaticClass();
	});

	return Out ? static_cast<T*>(*Out) : nullptr;
}
