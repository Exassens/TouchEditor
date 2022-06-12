// Copyright 2021 Lost in Game Studio. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityObject.h"
#include "TouchEditorCore.generated.h"

class UTouchEditorPreset;

USTRUCT(BlueprintType)
struct FTouchControl
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJoystick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BackgroundImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ThumbImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Center;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D VisualSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ThumbSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InteractionSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InputScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey HorizontalAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey VerticalAxis;

	FTouchControl() : Index(0), bIsJoystick(false), BackgroundImage(nullptr), ThumbImage(nullptr)
	{
		Center = FVector2D(0.5f, 0.5f);
		VisualSize = FVector2D(100, 100);
		ThumbSize = FVector2D(40, 40);
		InteractionSize = FVector2D(60, 60);
		InputScale = FVector2D(1, 1);
	}
};

USTRUCT(BlueprintType)
struct FTouchSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActiveOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InactiveOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUntilDesactivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPreventRecenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUntilReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartupDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivationDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeActivation;

	FTouchSettings() : ActiveOpacity(0.8f), InactiveOpacity(0.1f), TimeUntilDesactivate(0.5f), bPreventRecenter(false), bReset(false), TimeUntilReset(2.0f), StartupDelay(0.5f), bActivationDelay(false), TimeActivation(0)
	{

	}
};

/**
 *
 */
UCLASS(Blueprintable)
class TOUCHEDITOR_API UTouchEditorCore : public UObject
{
	GENERATED_BODY()

	//Constructor
	UTouchEditorCore();

public:

	//Create TouchInterface Asset
	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Create")
	bool CreateNew(FString AssetName, FString Path, UTouchInterface*& OutTouchInterface);

	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Create")
	bool CreateFromPreset(UTouchEditorPreset* Preset, FString AssetName, FString Path, UTouchInterface*& OutTouchInterface);

	//Modify TouchInterface Asset
	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Control")
	TArray<FTouchControl> GetTouchControl(const UTouchInterface* TouchInterface);

	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Control")
	bool SetControls(UTouchInterface* TouchInterface, TArray<FTouchControl> Controls, bool Save);


	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Settings")
	FTouchSettings GetTouchSettings(const UTouchInterface* TouchInterface);

	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Settings")
	bool SetTouchSettings(UTouchInterface* TouchInterface, const FTouchSettings TouchSettings, const bool Save);


	//Save TouchInterface Asset
	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Saving")
	bool SaveAsset(UTouchInterface* TouchInterface);

	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Interface Saving")
	bool SaveAssetAs(const FTouchSettings TouchSettings, const TArray<FTouchControl> Controls, FString AssetName, FString Path, UTouchInterface*& OutTouchInterface);


	//Create Preset Asset
	UFUNCTION(BlueprintCallable, Category = "Touch Editor | Preset")
	bool CreatePresetFromTouchInterface(const FTouchSettings TouchSettings, const TArray<FTouchControl> Controls, const FString AssetName);

	/**
	 * Call this function to destroy UObject instance.
	 * Warning : When this function is called, all references to this UObject Instance could be cleaned
	 */
	UFUNCTION(BlueprintCallable, Category = "Object")
	void Destroy();

private:
	UPROPERTY()
	TArray<FTouchControl> TouchControls;

	UFUNCTION()
	void SetControl(UTouchInterface* TouchInterface, FTouchControl Control);
};
