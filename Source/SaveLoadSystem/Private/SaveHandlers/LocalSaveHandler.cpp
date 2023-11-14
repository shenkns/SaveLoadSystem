// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2023.

#include "SaveHandlers/LocalSaveHandler.h"

#include "Log.h"
#include "Module/SaveLoadSystemSettings.h"
#include "SaveHandlers/Local/StatsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/StatsManager.h"
#include "Module/SaveLoadSystemModule.h"

DEFINE_LOG_CATEGORY_LOCAL(LogSaveLoadSystem);

bool ULocalSaveHandler::SaveProfileStats(TArray<UStat*> Stats)
{
	// Load Save Object Name
	FString SaveObjectName;
	if(const USaveLoadSystemSettings* Settings = GetDefault<USaveLoadSystemSettings>())
	{
		SaveObjectName = Settings->SaveObjectName;
	}
	else
	{
		SaveObjectName = "Profile";
	}

	if(UProfileSaveGame* SaveObject = Cast<UProfileSaveGame>(UGameplayStatics::CreateSaveGameObject(UProfileSaveGame::StaticClass())))
	{
		// Try To Serialize Profile Stats
		if(!USerializationSystemLibrary::ConvertObjectsToSaveData<UStat>(Stats, SaveObject->ProfileStatsSaveData)) return false;
		SaveObject->ProfileVersion = GetManager()->GetProfileStatsVersion();

		return UGameplayStatics::SaveGameToSlot(SaveObject, SaveObjectName, 0);
	}

	return false;
}

TArray<UStat*> ULocalSaveHandler::LoadProfileStats()
{
	TArray<UStat*> Stats;
	
	// Load Save Object Name
	FString SaveObjectName;
	if(const USaveLoadSystemSettings* Settings = GetDefault<USaveLoadSystemSettings>())
	{
		SaveObjectName = Settings->SaveObjectName;
	}
	else
	{
		SaveObjectName = "Save";
	}

	if(!UGameplayStatics::LoadGameFromSlot(SaveObjectName, 0))
	{
		LOG(Display, "No Save Object");
		
		return Stats;
	}

	// Load Profile Stats
	if(const UProfileSaveGame* SaveObject = Cast<UProfileSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveObjectName, 0)))
	{
		Stats = USerializationSystemLibrary::ConvertSaveDataToObjects<UStat>(SaveObject->ProfileStatsSaveData, GetManager());

		LOG(Display, "Loaded {} Stats", Stats.Num());
	}

	LOG(Display, "Invalid Save Object");

	return Stats;
}
