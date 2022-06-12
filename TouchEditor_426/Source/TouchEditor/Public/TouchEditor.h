// Copyright 2021 Lost in Game Studio. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FTouchEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
