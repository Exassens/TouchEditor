// Copyright 2021 Lost in Game Studio. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchEditorCore.h"
#include "Engine/DataAsset.h"
#include "TouchEditorPreset.generated.h"

/**
 *
 */
UCLASS()
class TOUCHEDITOR_API UTouchEditorPreset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//Touch Interface General Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Touch Editor | Preset")
		FTouchSettings PresetSettings;

	//Touch Interface Control Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Touch Editor | Preset")
		TArray<FTouchControl> PresetControls;

	//Used for categorization in asset selector widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Touch Editor | Preset")
		bool bInLandscapeMode;
};
