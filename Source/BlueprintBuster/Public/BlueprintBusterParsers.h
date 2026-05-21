// Copyright (c) 2026 Shumov Sergey. All Rights Reserved.
// Plugin: BlueprintBuster

// BlueprintBusterParsers.h
// Static parser entry points — one per Blueprint subsystem (SCS / CDO / Graph).
// No state, no UPROPERTY members — these are pure functions over a UBlueprint*.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintBusterTypes.h"

class UBlueprint;
class UEdGraphNode;
class UEdGraphPin;

namespace BlueprintBusterParsers
{
    // Fills OutComponents with the entire SCS hierarchy of InBlueprint.
    // Order is depth-first starting from the root scene component.
    void ParseSimpleConstructionScript(UBlueprint* InBlueprint,
                                       TArray<FBPComponentInfo>& OutComponents);

    // Fills OutDefaults with CDO properties whose values differ from the parent CDO.
    // Skips Transient / EditorOnly / DuplicateTransient properties.
    void ParseClassDefaultObject(UBlueprint* InBlueprint,
                                 TArray<FBPPropertyInfo>& OutDefaults);

    // Walks every Ubergraph + ConstructionScript page, extracting one event tree
    // per UK2Node_Event entry. MaxDepth bounds recursion to prevent runaway graphs.
    void ParseExecutionGraphs(UBlueprint* InBlueprint,
                              TArray<FBPEventTreeInfo>& OutEventTrees,
                              int32& OutUnsupportedCount,
                              int32& OutTotalNodeCount,
                              int32 MaxDepth = 64);

    // Walks UBlueprint::FunctionGraphs (excluding UserConstructionScript) and
    // extracts a FBPCustomFunctionInfo per custom function: signature pulled
    // from UK2Node_FunctionEntry inputs and UK2Node_FunctionResult outputs;
    // body traced from the Entry node's Then exec pin via TraceLinearChain.
    void ParseFunctionGraphs(UBlueprint* InBlueprint,
                             TArray<FBPCustomFunctionInfo>& OutFunctions,
                             int32& OutUnsupportedCount,
                             int32& OutTotalNodeCount,
                             int32 MaxDepth = 64);
}
