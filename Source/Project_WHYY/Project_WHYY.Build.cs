// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_WHYY : ModuleRules
{
	public Project_WHYY(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] 
		{
			"Project_WHYY",
		});

		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"UMG",
				"GameplayTags",				// GameplayTags를 사용하기 위해(WHYCharacterMovementComponenet.h파일)
				"GameplayTasks",
                "GameplayAbilities",		// GameplayAbilities 플러그인을 사용
				"AIModule",					// GenericTeamAgentInterface.h를 사용하기 위해
            });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
