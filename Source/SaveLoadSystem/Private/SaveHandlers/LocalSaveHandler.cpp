// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#include "SaveHandlers/LocalSaveHandler.h"

#include "Module/SaveLoadSystemSettings.h"
#include "SaveHandlers/Local/StatsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LogSystem.h"

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
		DEBUG_MESSAGE(GetDefault<USaveLoadSystemSettings>()->bShowDebugMessages, LogSaveLoadSystemSettings, "No Save Object")
		
		return Stats;
	}

	// Load Profile Stats
	if(const UProfileSaveGame* SaveObject = Cast<UProfileSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveObjectName, 0)))
	{
		Stats = USerializationSystemLibrary::ConvertSaveDataToObjects<UStat>(SaveObject->ProfileStatsSaveData, GetManager());

		DEBUG_MESSAGE(GetDefault<USaveLoadSystemSettings>()->bShowDebugMessages, LogSaveLoadSystemSettings, "Loaded %d Stats", Stats.Num())
	}

	DEBUG_MESSAGE(GetDefault<USaveLoadSystemSettings>()->bShowDebugMessages, LogSaveLoadSystemSettings, "Invalid Save Object")

	return Stats;
}
