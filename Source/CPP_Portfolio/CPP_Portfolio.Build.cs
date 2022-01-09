// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPP_Portfolio : ModuleRules
{
    public CPP_Portfolio(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "SlateCore",
            "Niagara",
            "NavigationSystem",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });


        PublicIncludePaths.Add(ModuleDirectory);
    }
}
