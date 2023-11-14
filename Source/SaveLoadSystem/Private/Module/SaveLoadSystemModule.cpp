// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Module/SaveLoadSystemModule.h"

#include "Log.h"
#include "Log/Details/LocalLogCategory.h"
#include "Module/SaveLoadSystemSettings.h"

#if UE_EDITOR
#include "ISettingsModule.h"
#endif

IMPLEMENT_MODULE(FSaveLoadSystemModule, SaveLoadSystem)

SAVELOADSYSTEM_API DEFINE_LOG_CATEGORY(LogSaveLoadSystem);
DEFINE_LOG_CATEGORY_LOCAL(LogSaveLoadSystem);

void FSaveLoadSystemModule::StartupModule()
{
#if UE_EDITOR
	RegisterSystemSettings();
#endif
}

void FSaveLoadSystemModule::ShutdownModule()
{
#if UE_EDITOR
	UnregisterSystemSettings();
#endif
}

#if UE_EDITOR
void FSaveLoadSystemModule::RegisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Save-Load System",
			FText::FromString(TEXT("Save-Load System")),
			FText::FromString(TEXT("Configuration settings for Stats System")),
			GetMutableDefault<USaveLoadSystemSettings>()
		);

		LOG(Display, "Save-Load System Settings Registered");
	}
}

void FSaveLoadSystemModule::UnregisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Save-Load System");

		LOG(Display, "Save-Load System Settings Unregistered");
	}
}
#endif
