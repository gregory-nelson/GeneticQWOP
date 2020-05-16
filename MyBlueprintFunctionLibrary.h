// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

using namespace std;

/**
 *
 */
UCLASS()
class AI_PROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		struct Gait {
		int32 fitness;
		int32 length;
		int32 variation;
		FString chromosome;

		Gait(FString chrom, int32 score, int32 len, int32 variation);

		FString mate(Gait gait2);
	};

	struct Simulation {
		TArray<Gait> population;
		int32 variation;
		Simulation(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, int32 variation);
		TArray<FString> cycle(int32 numChroms);
	};

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary")
		static TArray<FString> run(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, bool first, int32 variation);

};