// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#include "Stats/InfoStat.h"

int UInfoStat::GetIntStat(const FName StatName) const
{
	if(!InfoStats.Contains(StatName)) return 0;
	FString const * Value = InfoStats.Find(StatName);
	if(Value)
	{
		return FCString::Atoi(**Value);
	}

	return 0;
}

float UInfoStat::GetFloatStat(const FName StatName) const
{
	FString const * Value = InfoStats.Find(StatName);
	if(Value)
	{
		return FCString::Atof(**Value);
	}

	return 0.f;
}

FString UInfoStat::GetStringStat(const FName StatName) const
{
	FString const * Value = InfoStats.Find(StatName);
	if(Value) return *Value;

	return "";
}

void UInfoStat::SetIntStat(const FName StatName, int Value)
{
	InfoStats.Add(StatName, FString::Printf(TEXT("%d"), Value));
}

void UInfoStat::SetFloatStat(const FName StatName, float Value)
{
	InfoStats.Add(StatName, FString::SanitizeFloat(Value));
}

void UInfoStat::SetStringStat(const FName StatName, FString Value)
{
	InfoStats.Add(StatName, Value);
}
