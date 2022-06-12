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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	bool bIsJoystick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	UTexture2D* BackgroundImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	UTexture2D* ThumbImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FVector2D Center;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FVector2D VisualSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FVector2D ThumbSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FVector2D InteractionSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FVector2D InputScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
	FKey HorizontalAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Control")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	float ActiveOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	float InactiveOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	float TimeUntilDesactivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	bool bPreventRecenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	bool bReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	float TimeUntilReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	float StartupDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
	bool bActivationDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Touch Settings")
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
