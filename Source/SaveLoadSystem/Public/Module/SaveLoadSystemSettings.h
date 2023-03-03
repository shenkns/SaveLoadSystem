// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

#pragma once

#include "UObject/Object.h"

#include "UObject/SoftObjectPtr.h"
#include "Libs/SerializationSystemLibrary.h"
#include "SaveHandlers/LocalSaveHandler.h"

#include "SaveLoadSystemSettings.generated.h"

class UStat;
class USaveHandler;

SAVELOADSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogSaveLoadSystemSettings, Log, All);

UCLASS(Config=Game, DefaultConfig)
class SAVELOADSYSTEM_API USaveLoadSystemSettings : public UObject
{
	GENERATED_BODY()

public:

	// Configuration For Save-Load System

	// Stats
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Stats")
	TArray<UStat*> Stats;
	
	UPROPERTY(EditDefaultsOnly, Config, Category = "Stats")
	TArray<TSoftClassPtr<UStat>> DefaultStats;

	UPROPERTY(Config)
	TArray<FObjectSaveData> StatsSaveData;

	UPROPERTY(EditDefaultsOnly, Config, Category = "SaveHandler")
	TSoftClassPtr<USaveHandler> SaveHandlerClass = ULocalSaveHandler::StaticClass();

	UPROPERTY(EditDefaultsOnly, Config, Category = "SaveHandler")
	FString SaveObjectName = FString("Save");

	// Debug
	UPROPERTY(Config, EditDefaultsOnly, Category = "Debug")
	bool bShowDebugMessages;

public:

	virtual void PostInitProperties() override;

#if UE_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void SaveSettings();
};
