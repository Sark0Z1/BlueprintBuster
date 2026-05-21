// Copyright (c) 2026 Shumov Sergey. All Rights Reserved.
// Plugin: BlueprintBuster

// BlueprintBuster.cpp

#include "BlueprintBuster.h"

DEFINE_LOG_CATEGORY(LogBlueprintBuster);

#define LOCTEXT_NAMESPACE "FBlueprintBusterModule"

void FBlueprintBusterModule::StartupModule()
{
    UE_LOG(LogBlueprintBuster, Log,
           TEXT("BlueprintBuster module started. Run via "
                "UnrealEditor-Cmd.exe <Project.uproject> -run=BlueprintBuster -TargetBP=... -OutputDir=..."));
}

void FBlueprintBusterModule::ShutdownModule()
{
    UE_LOG(LogBlueprintBuster, Log, TEXT("BlueprintBuster module shut down."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBlueprintBusterModule, BlueprintBuster)
