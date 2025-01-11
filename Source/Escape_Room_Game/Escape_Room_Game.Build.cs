// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Escape_Room_Game : ModuleRules
{
	public Escape_Room_Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
