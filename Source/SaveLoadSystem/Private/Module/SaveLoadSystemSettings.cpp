// Copyright shenkns Managers System Developed With Unreal Engine. All Rights Reserved 2022.

#include "Module/SaveLoadSystemSettings.h"

#include "Stats/Stat.h"
#include "Libs/SerializationSystemLibrary.h"
#include "LogSystem.h"

SAVELOADSYSTEM_API DEFINE_LOG_CATEGORY(LogSaveLoadSystemSettings);

void USaveLoadSystemSettings::PostInitProperties()
{
	Super::PostInitProperties();
	
	Stats = USerializationSystemLibrary::ConvertSaveDataToObjects<UStat>(StatsSaveData, this);

	LOG(LogSaveLoadSystemSettings, "Stats Objects Settings Loaded")
}

#if UE_EDITOR
void USaveLoadSystemSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(CastField<FArrayProperty>(PropertyChangedEvent.MemberProperty))
	{
		USerializationSystemLibrary::ConvertObjectsToSaveData<UStat>(Stats, StatsSaveData);

		SaveSettings();

		LOG(LogSaveLoadSystemSettings, "Profile Objects Settings Saved To Config")
	}
}
#endif

void USaveLoadSystemSettings::SaveSettings()
{
	SaveConfig(CPF_Config, *GetDefaultConfigFilename(), new FConfigCacheIni(EConfigCacheType::DiskBacked), true);
	UpdateDefaultConfigFile();
}
