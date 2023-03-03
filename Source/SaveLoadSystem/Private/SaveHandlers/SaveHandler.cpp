// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#include "SaveHandlers/SaveHandler.h"

#include "ManagersSystem.h"
#include "Managers/StatsManager.h"

UWorld* USaveHandler::GetWorld() const
{
	return GetOuter() ? GetOuter()->GetWorld() : nullptr;
}

UManagersSystem* USaveHandler::GetManagersSystem() const
{
	return Cast<UManagersSystem>(GetOuter()-> GetOuter());
}

UStatsManager* USaveHandler::GetManager() const
{
	return Cast<UStatsManager>(GetOuter());
}

bool USaveHandler::SaveProfileStats(TArray<UStat*> Stats)
{
	// Blueprint Implementation
	return SaveProfile(Stats);
}

bool USaveHandler::SaveProfile_Implementation(const TArray<UStat*>& Stats)
{
	return false;
}

TArray<UStat*> USaveHandler::LoadProfileStats()
{
	// Blueprint Implementation
	TArray<UStat*> Stats;
	LoadProfile(Stats);

	return Stats;
}

bool USaveHandler::LoadProfile_Implementation(TArray<UStat*>& Stats)
{
	return false;
}
