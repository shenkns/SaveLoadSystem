// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "Stats/Stat.h"
#include "InfoStat.generated.h"

UCLASS()
class SAVELOADSYSTEM_API UInfoStat : public UStat
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Profile|Stats")
	TMap<FName, FString> InfoStats;

public:

	UFUNCTION(BlueprintPure, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "Int"))
	int GetIntStat(const FName StatName) const;

	UFUNCTION(BlueprintPure, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "Float"))
	float GetFloatStat(const FName StatName) const;

	UFUNCTION(BlueprintPure, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "String"))
	FString GetStringStat(const FName StatName) const;

	UFUNCTION(BlueprintCallable, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "Int"))
	void SetIntStat(const FName StatName, int Value);

	UFUNCTION(BlueprintCallable, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "Float"))
	void SetFloatStat(const FName StatName, float Value);

	UFUNCTION(BlueprintCallable, Category = "Profile|Stats|Info", meta = (CompactNodeTitle = "String"))
	void SetStringStat(const FName StatName, FString Value);
};
