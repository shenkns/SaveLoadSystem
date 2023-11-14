// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Managers/StatsManager.h"

#include "Log.h"
#include "ManagersSystem.h"
#include "Log/Details/LocalLogCategory.h"
#include "Module/SaveLoadSystemModule.h"
#include "Module/SaveLoadSystemSettings.h"
#include "SaveHandlers/SaveHandler.h"

DEFINE_LOG_CATEGORY_LOCAL(LogSaveLoadSystem);

void UStatsManager::InitManager()
{
	Super::InitManager();	

	// Stats Initialization
	InitSaveHandler();
	InitStats();
	SaveStats();
}

// Profile Stat Getter
UStat* UStatsManager::GetStat(TSubclassOf<UStat> Class) const
{
	// Find Stat
	UStat* const* Out = Stats.FindByPredicate([Class](const UStat* Src)
	{
		return Src && Src->GetClass() == Class;
	});

	return Out ? *Out : nullptr;
}

void UStatsManager::InitSaveHandler()
{
	// Get Save Handler Class
	UClass* SaveHandlerClass;
	if(const USaveLoadSystemSettings* Settings = GetDefault<USaveLoadSystemSettings>())
	{
		if(Settings->SaveHandlerClass.LoadSynchronous())
		{
			SaveHandlerClass = Settings->SaveHandlerClass.LoadSynchronous();
		}
		else
		{
			SaveHandlerClass = USaveHandler::StaticClass();
		}
	}
	else
	{
		SaveHandlerClass = USaveHandler::StaticClass();
	}

	SaveHandler = NewObject<USaveHandler>(this, SaveHandlerClass);

	LOG(Display, "Save Handler Initialized");
}

void UStatsManager::InitStats()
{
	Stats.Empty();

	LoadProfileStats();
	CreateNewProfileStats();

	LOG(Display, "Stats Initialized");
}

bool UStatsManager::SaveStats()
{
	// Check Save Handler
	if(!SaveHandler) return false;
	return SaveHandler->SaveProfileStats(Stats);
}


void UStatsManager::LoadProfileStats()
{
	// Check Save Handler
	if(!SaveHandler) return;

	// Iterate Loaded Stats
	for(UStat* Stat : SaveHandler->LoadProfileStats())
	{
		if(GetStat(Stat->GetClass())) continue;

		Stat->InitStat();
		
		Stats.Add(Stat);
	}

	LOG(Display, "Stats Loaded");
}

void UStatsManager::CreateNewProfileStats()
{
	const USaveLoadSystemSettings* Settings = GetDefault<USaveLoadSystemSettings>();
	if(!Settings) return;

	// Initialize New Profile Stats

	for(const UStat* TemplateStat : Settings->Stats)
	{
		if(!TemplateStat) continue;
		if(GetStat(TemplateStat->GetClass())) continue;

		UStat* Stat = DuplicateObject<UStat>(TemplateStat, this);
		Stat->InitStat();

		Stats.Add(Stat);
	}

	for(TSoftClassPtr<UStat> StatSoftClass : Settings->DefaultStats)
	{
		UClass* StatClass = StatSoftClass.LoadSynchronous();
		if(!StatClass) continue;
		if(GetStat(StatClass)) continue;

		UStat* Stat = NewObject<UStat>(this, StatClass);
		Stat->InitStat();

		Stats.Add(Stat);
	}
	
	LOG(Display, "New Stats Created");
}
