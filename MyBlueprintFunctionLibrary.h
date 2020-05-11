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
class MYPROJECT3_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	struct Gait {
		int32 fitness;
		int32 length;
		FString chromosome;
		
		Gait(FString chrom, int32 score, int32 len);

		FString mate(Gait gait2);
	};

	static bool compareFit(Gait & g1, Gait & g2) {
		return g1.fitness < g2.fitness;
	}

    struct Simulation {
        TArray<Gait> population;
		Simulation(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms);
		TArray<FString> cycle(int32 numChroms);
		TArray<FString> sort(TArray<Gait> g);
    };



	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
	TArray<FString> run(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, bool first);
	
};
