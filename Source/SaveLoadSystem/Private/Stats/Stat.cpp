// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#include "Stats/Stat.h"

#include "ManagersSystem.h"
#include "Module/SaveLoadSystemSettings.h"
#include "Managers/StatsManager.h"

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
	
	DEBUG_MESSAGE(GetDefault<USaveLoadSystemSettings>()->bShowDebugMessages, LogSaveLoadSystemSettings, "%s Initialization", *GetName())

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
