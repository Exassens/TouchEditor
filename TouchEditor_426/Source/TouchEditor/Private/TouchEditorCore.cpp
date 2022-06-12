// Copyright 2021 Lost in Game Studio. All Right Reserved


#include "TouchEditorCore.h"
#include "IAssetTools.h"
#include "GameFramework/TouchInterface.h"
#include "EditorScriptingUtilities/Public/EditorAssetLibrary.h"
#include "AssetToolsModule.h"
#include "TouchEditorPreset.h"


UTouchEditorCore::UTouchEditorCore()
{

}

//CREATE ASSET
bool UTouchEditorCore::CreateNew(const FString AssetName, const FString Path, UTouchInterface*& OutTouchInterface)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* AssetCreated = AssetTools.CreateAsset(AssetName, Path, UTouchInterface::StaticClass(), nullptr, NAME_None);

	if (AssetCreated)
	{
		UTouchInterface* TouchInterface = Cast<UTouchInterface>(AssetCreated);
		OutTouchInterface = TouchInterface;
		return UEditorAssetLibrary::SaveLoadedAsset(TouchInterface, false);
	}

	OutTouchInterface = nullptr;
	return false;
}

bool UTouchEditorCore::CreateFromPreset(UTouchEditorPreset* Preset, FString AssetName, FString Path, UTouchInterface*& OutTouchInterface)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* AssetCreated = AssetTools.CreateAsset(AssetName, Path, UTouchInterface::StaticClass(), nullptr, NAME_None);

	if (AssetCreated)
	{
		UTouchInterface* TouchInterface = Cast<UTouchInterface>(AssetCreated);
		SetControls(TouchInterface, Preset->PresetControls, false);
		SetTouchSettings(TouchInterface, Preset->PresetSettings, false);
		OutTouchInterface = TouchInterface;
		return UEditorAssetLibrary::SaveLoadedAsset(TouchInterface, false);
	}

	OutTouchInterface = nullptr;
	return false;
}

//SAVE ASSET
bool UTouchEditorCore::SaveAsset(UTouchInterface* TouchInterface)
{
	return UEditorAssetLibrary::SaveLoadedAsset(TouchInterface, false);
}

bool UTouchEditorCore::SaveAssetAs(const FTouchSettings TouchSettings, const TArray<FTouchControl> Controls, FString AssetName, FString Path, UTouchInterface*& OutTouchInterface)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* AssetCreated = AssetTools.CreateAsset(AssetName, Path, UTouchInterface::StaticClass(), nullptr, NAME_None);

	if (AssetCreated)
	{
		UTouchInterface* TouchInterfaceCreated = Cast<UTouchInterface>(AssetCreated);
		//Set Controls
		SetControls(TouchInterfaceCreated, Controls, false);
		//Set Settings
		SetTouchSettings(TouchInterfaceCreated, TouchSettings, false);
		OutTouchInterface = TouchInterfaceCreated;
		//Save
		return UEditorAssetLibrary::SaveLoadedAsset(TouchInterfaceCreated, false);
	}

	OutTouchInterface = nullptr;
	return false;
}

//CREATE PRESET
bool UTouchEditorCore::CreatePresetFromTouchInterface(const FTouchSettings TouchSettings, const TArray<FTouchControl> Controls, const FString AssetName)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	UObject* AssetCreated = AssetTools.CreateAsset(AssetName, TEXT("/TouchEditor/Presets"), UTouchEditorPreset::StaticClass(), nullptr, NAME_None);

	if (AssetCreated)
	{
		UTouchEditorPreset* Preset = Cast<UTouchEditorPreset>(AssetCreated);
		Preset->PresetSettings = TouchSettings;
		Preset->PresetControls = Controls;
		return UEditorAssetLibrary::SaveLoadedAsset(Preset, false);
	}

	return false;
}

//GETTERS
TArray<FTouchControl> UTouchEditorCore::GetTouchControl(const UTouchInterface* TouchInterface)
{
	TArray<FTouchControl> LocalTouchControls;

	if (!TouchInterface)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Touch Interface is invalid, return null"));
		return LocalTouchControls;
	}

	TArray<FTouchInputControl> TouchInputControls = TouchInterface->Controls;

	if (TouchInputControls.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Controls array is empty, return null"));
		return LocalTouchControls;
	}

	for (int Itr = 0; Itr < TouchInputControls.Num(); Itr++)
	{
		FTouchControl TouchControl;

		TouchControl.Index = Itr;
		TouchControl.Center = TouchInputControls[Itr].Center;
		TouchControl.BackgroundImage = TouchInputControls[Itr].Image2;
		TouchControl.ThumbImage = TouchInputControls[Itr].Image1;
		TouchControl.VisualSize = TouchInputControls[Itr].VisualSize;
		TouchControl.InteractionSize = TouchInputControls[Itr].InteractionSize;
		TouchControl.ThumbSize = TouchInputControls[Itr].ThumbSize;
		TouchControl.InputScale = TouchInputControls[Itr].InputScale;
		TouchControl.HorizontalAxis = TouchInputControls[Itr].MainInputKey;
		TouchControl.VerticalAxis = TouchInputControls[Itr].AltInputKey;

		if (TouchInputControls[Itr].Image1)
			TouchControl.bIsJoystick = true;
		else
			TouchControl.bIsJoystick = false;

		LocalTouchControls.Add(TouchControl);
	}

	return LocalTouchControls;
}

FTouchSettings UTouchEditorCore::GetTouchSettings(const UTouchInterface* TouchInterface)
{
	FTouchSettings TouchSettings;

	TouchSettings.ActiveOpacity = TouchInterface->ActiveOpacity;
	TouchSettings.InactiveOpacity = TouchInterface->InactiveOpacity;
	TouchSettings.TimeUntilDesactivate = TouchInterface->TimeUntilDeactive;
	TouchSettings.bPreventRecenter = TouchInterface->bPreventRecenter;
	TouchSettings.bReset = TouchInterface->TimeUntilReset > 0;
	TouchSettings.TimeUntilReset = TouchInterface->TimeUntilReset;
	TouchSettings.StartupDelay = TouchInterface->StartupDelay;
	TouchSettings.bActivationDelay = TouchInterface->ActivationDelay > 0;
	TouchSettings.TimeActivation = TouchInterface->ActivationDelay;

	return TouchSettings;
}

//SETTERS
void UTouchEditorCore::SetControl(UTouchInterface* TouchInterface, FTouchControl Control)
{
	FTouchInputControl TouchInputControl;
	TouchInputControl.Center = Control.Center;
	TouchInputControl.Image1 = Control.ThumbImage;
	TouchInputControl.Image2 = Control.BackgroundImage;
	TouchInputControl.InputScale = Control.InputScale;
	TouchInputControl.InteractionSize = Control.InteractionSize;
	TouchInputControl.ThumbSize = Control.ThumbSize;
	TouchInputControl.VisualSize = Control.VisualSize;
	TouchInputControl.AltInputKey = Control.VerticalAxis;
	TouchInputControl.MainInputKey = Control.HorizontalAxis;

	TouchInterface->Controls.Add(TouchInputControl);
}

bool UTouchEditorCore::SetControls(UTouchInterface* TouchInterface, TArray<FTouchControl> Controls, bool Save)
{
	if (!TouchInterface)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Touch Interface parameter is null"));
		return false;
	}

	TouchInterface->Controls = TArray<FTouchInputControl>();

	for (auto Control : Controls)
	{
		SetControl(TouchInterface, Control);
	}

	if (Save)
	{
		return UEditorAssetLibrary::SaveLoadedAsset(TouchInterface, false);
	}

	return true;
}

bool UTouchEditorCore::SetTouchSettings(UTouchInterface* TouchInterface, const FTouchSettings TouchSettings, const bool Save)
{
	if (!TouchInterface)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Touch Interface parameter is null"));
		return false;
	}

	TouchInterface->ActiveOpacity = TouchSettings.ActiveOpacity;
	TouchInterface->InactiveOpacity = TouchSettings.InactiveOpacity;
	TouchInterface->TimeUntilDeactive = TouchSettings.TimeUntilDesactivate;
	TouchInterface->bPreventRecenter = TouchSettings.bPreventRecenter;
	TouchInterface->TimeUntilReset = TouchSettings.bReset ? TouchSettings.TimeUntilReset : 0;
	TouchInterface->StartupDelay = TouchSettings.StartupDelay;
	TouchInterface->ActivationDelay = TouchSettings.bActivationDelay ? TouchSettings.TimeActivation : 0;

	if (Save)
	{
		return SaveAsset(TouchInterface);
	}

	return true;
}

void UTouchEditorCore::Destroy()
{
	ConditionalBeginDestroy();
}

