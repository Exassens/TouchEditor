// Copyright 2021 Lost in Game Studio. All Right Reserved

#include "TouchEditor.h"

#define LOCTEXT_NAMESPACE "FTouchEditorModule"

void FTouchEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTouchEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTouchEditorModule, TouchEditor)