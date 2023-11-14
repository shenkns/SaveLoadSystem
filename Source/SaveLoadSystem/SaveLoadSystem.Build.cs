// Copyright shenkns Save-Load System Developed With Unreal Engine. All Rights Reserved 2022.

using UnrealBuildTool;

public class SaveLoadSystem : ModuleRules
{
	public SaveLoadSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;

		PrivateIncludePaths.AddRange(
			new string[] {
				"SaveLoadSystem/Public/"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"ManagersSystem",
				"SerializationSystem",
				"LogSystem"
			}
		);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[]
			{
				"ManagersSystem",
				"SerializationSystem",
				"LogSystem"
			}
		);
	}
}
