// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "Modules/ModuleManager.h"

SAVELOADSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogSaveLoadSystem, Log, All)

class FSaveLoadSystemModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:

#if UE_EDITOR
	// Init Stats Configuration
	void RegisterSystemSettings() const;
	void UnregisterSystemSettings() const;
#endif
};
