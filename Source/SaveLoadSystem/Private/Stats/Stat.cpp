// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Stats/Stat.h"

#include "Log.h"
#include "ManagersSystem.h"
#include "Module/SaveLoadSystemSettings.h"
#include "Managers/StatsManager.h"
#include "Module/SaveLoadSystemModule.h"

DEFINE_LOG_CATEGORY_LOCAL(LogSaveLoadSystem);

UWorld* UStat::GetWorld() const
{
	if(GetOuter()) return GetOuter()->GetWorld();
	return nullptr;
}

void UStat::InitStat()
{
	if(GetClass()->ImplementsInterface(USerializationInterface::StaticClass()))
	{
		if(!ISerializationInterface::Execute_PostConvertFromSaveData(this)) return;
	}
	
	LOG(Display, "{} Initialization", this);

	Init();
}

UManagersSystem* UStat::GetManagersSystem() const
{
	return Cast<UManagersSystem>(GetOuter()->GetOuter());
}

UStatsManager* UStat::GetManager() const
{
	return Cast<UStatsManager>(GetOuter());
}
