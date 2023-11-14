// Copyright shenkns Managers System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Module/SaveLoadSystemSettings.h"

#include "Log.h"
#include "Stats/Stat.h"
#include "Libs/SerializationSystemLibrary.h"
#include "Log/Details/LocalLogCategory.h"

SAVELOADSYSTEM_API DEFINE_LOG_CATEGORY(LogSaveLoadSystemSettings);
DEFINE_LOG_CATEGORY_LOCAL(LogSaveLoadSystemSettings);

void USaveLoadSystemSettings::PostInitProperties()
{
	Super::PostInitProperties();
	
	Stats = USerializationSystemLibrary::ConvertSaveDataToObjects<UStat>(StatsSaveData, this);

	LOG(Display, "Stats Objects Settings Loaded");
}

#if UE_EDITOR
void USaveLoadSystemSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(CastField<FArrayProperty>(PropertyChangedEvent.MemberProperty))
	{
		USerializationSystemLibrary::ConvertObjectsToSaveData<UStat>(Stats, StatsSaveData);

		SaveSettings();

		LOG(Display, "Profile Objects Settings Saved To Config");
	}
}
#endif

void USaveLoadSystemSettings::SaveSettings()
{
	SaveConfig(CPF_Config, *GetDefaultConfigFilename(), new FConfigCacheIni(EConfigCacheType::DiskBacked), true);
	UpdateDefaultConfigFile();
}
