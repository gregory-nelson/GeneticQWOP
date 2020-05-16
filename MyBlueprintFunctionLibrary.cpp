// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

const char MOVES[17] = "QALPWERTYUSDFGZX";

UMyBlueprintFunctionLibrary::Simulation::Simulation(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, int32 variation)
{
	variation = variation;
	for (int32 i = 0; i < numChroms; i += 1) {
		population.Add(Gait(gen[i], scores[i], lenChroms, variation));
	}
}

TArray<FString> UMyBlueprintFunctionLibrary::run(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, bool first, int32 variation)
{
	srand(time(NULL));
	if (first) {
		TArray<FString> population;
		for (int32 ndx = 0; ndx < numChroms; ndx += 1) {
			FString chromosome = "";
			for (int32 i = 0; i < lenChroms; i = i + 1) {
				int32 move = rand() % 16;
				chromosome += MOVES[move];
				chromosome += ",";
			}
			population.Add(chromosome);
		}
		return population;
	}
	else {
		Simulation sim = Simulation(gen, scores, numChroms, lenChroms, variation);
		return sim.cycle(numChroms);
	}
}

TArray<FString> UMyBlueprintFunctionLibrary::Simulation::cycle(int32 numChroms) {
	TArray<FString> new_generation;
	TArray<Gait> pop;

	while (population.Num() > 0) {
		int32 max = 0;
		int32 n = 0;
		for (int ndx = 0; ndx < population.Num(); ndx += 1) {
			if (max < population[ndx].fitness) {
				max = population[ndx].fitness;
				n = ndx;
			}
		}
		pop.Add(population[n]);
		population.RemoveAt(n);
	}
	if (variation < 4) {
		for (int32 ndx = 0; ndx < numChroms; ndx += 1) {
			Gait m1 = pop[(rand() % (numChroms / 2))];
			Gait m2 = pop[(rand() % (numChroms / 2))];
			FString child = m1.mate(m2);
			new_generation.Add(child);
		}
		return new_generation;
	}
	else {

		for (int32 ndx = 0; ndx < (numChroms - (numChroms / 10)); ndx += 1) {
			Gait m1 = pop[(rand() % (numChroms / 2))];
			Gait m2 = pop[(rand() % (numChroms / 2))];
			FString child = m1.mate(m2);
			new_generation.Add(child);
		}
		for (int32 ndx = 0; ndx < numChroms / 10; ndx += 1) {
			FString child = pop[ndx].chromosome;
			new_generation.Add(child);
		}
		return new_generation;

	}
}

FString UMyBlueprintFunctionLibrary::Gait::mate(Gait gait2) {
	FString child = "";

	if (variation == 2 || variation == 5) {
		//two point crossover, p is the end of the first section (dna comes from gait 1)
		//from (p,p+q) we take dna from gait 2
		//from(p+q, end) we take dna from gait 1
		int32 p = rand() % length;
		int32 q = p + rand() % (int32)(length - p);
		//from 0 to p take dna from gait 1 with a 5% chance of mutation
		for (int32 ndx = 0; ndx < p; ndx += 1) {
			float prob = rand() % 20;
			if (prob < 19) {
				child += chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}
		//from p to p+q take dna from gait 2 with a 5% chance of mutation
		for (int32 ndx = p; ndx < q; ndx += 1) {
			float prob = rand() % 20;
			if (prob < 19) {
				child += gait2.chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}
		//from p+q to the end take dna from gait 1 with a 5% chance of mutation
		for (int32 ndx = q; ndx < length; ndx += 1) {
			float prob = rand() % 20;
			if (p < 19) {
				child += chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}
	}
	else if (variation == 1 || variation == 4) {
		int32 p = rand() % length;
		for (int32 ndx = 0; ndx < p; ndx += 1) {
			float prob = rand() % 20;
			if (prob < 19) {
				child += chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}
		for (int32 ndx = p; ndx < length; ndx += 1) {
			float prob = rand() % 20;
			if (prob < 19) {
				child += gait2.chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}

	}
	else {
		for (int32 ndx = 0; ndx < length; ndx += 1) {
			float prob = rand() % 40;
			if (prob < 19) {
				child += chromosome[ndx * 2];
			}
			else if (prob < 38) {
				child += gait2.chromosome[ndx * 2];
			}
			else {
				child += MOVES[rand() % 16];
			}
			child += ",";
		}
	}
	return child;
}

UMyBlueprintFunctionLibrary::Gait::Gait(FString chrom, int32 score, int32 len, int32 variation) {
	chromosome = chrom;
	fitness = score;
	length = len;
	variation = variation;
}