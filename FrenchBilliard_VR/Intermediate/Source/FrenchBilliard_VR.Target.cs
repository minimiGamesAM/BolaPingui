using UnrealBuildTool;

public class FrenchBilliard_VRTarget : TargetRules
{
	public FrenchBilliard_VRTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.V2;
		Type = TargetType.Game;
		ExtraModuleNames.Add("FrenchBilliard_VR");
	}
}
