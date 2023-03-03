// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "UObject/Object.h"

#include "Stat.generated.h"

class UManagersSystem;
class UStatsManager;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SAVELOADSYSTEM_API UStat : public UObject
{
	GENERATED_BODY()

protected:
	
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Profile|Replication")
	//bool Replicated = false;

public:

	virtual UWorld* GetWorld() const override;

	virtual void InitStat();

	UFUNCTION(BlueprintPure, Category = "Profile", meta = (CompactNodeTitle = "System"))
	UManagersSystem* GetManagersSystem() const;

	UFUNCTION(BlueprintPure, Category = "Profile", meta = (CompactNodeTitle = "Manager"))
	UStatsManager* GetManager() const;

protected:

	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintProtected))
	void Init();
};
