// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

const char MOVES[17] = "pdcjbihnagfmelko";

//struct Gait {
//    int32 fitness = 0;
//    int32 length = 20;
//    FString chromosome;
//    Gait(FString chrom, int32 score) {
//        chromosome = chrom;
//        fitness = score;
//    }
//    FString mate(Gait gait2) {
//        FString child = "";
//        //two point crossover, p is the end of the first section (dna comes from gait 1)
//        //from (p,p+q) we take dna from gait 2
//        //from(p+q, end) we take dna from gait 1
//        int32 p = rand() % 19;
//        int32 q = p + rand() % (int32)(20 - p);
//        //from 0 to p take dna from gait 1 with a 5% chance of mutation
//        for (int32 ndx = 0; ndx < p; ndx += 1) {
//            float prob = rand() % 20;
//            if (prob < 19) {
//                child += chromosome[ndx];
//            }
//            else {
//                child += MOVES[rand() % 16];
//            }
//            child += ",";
//        }
//        //from p to p+q take dna from gait 2 with a 5% chance of mutation
//        for (int32 ndx = p; ndx < q; ndx += 1) {
//            float prob = rand() % 20;
//            if (prob < 19) {
//                child += gait2.chromosome[ndx];
//            }
//            else {
//                child += MOVES[rand() % 16];
//            }
//            child += ",";
//        }
//        //from p+q to the end take dna from gait 1 with a 5% chance of mutation
//        for (int32 ndx = q; ndx < 20; ndx += 1) {
//            float prob = rand() % 20;
//            if (p < 19) {
//                child += chromosome[ndx];
//            }
//            else {
//                child += MOVES[rand() % 16];
//            }
//            child += ",";
//        }
//        return child;
//    }
//};

//struct Simulation {
//    TArray<Gait> population;
//    Simulation(TArray<FString> gen, TArray<int32> scores, int32 numChroms) {
//        for (int32 i = 0; i < numChroms; i += 1) {
//            population.Add(Gait(gen[i], scores[i]));
//        }
//    }
//    TArray<FString> cycle() {
//        TArray<FString> new_generation = sort(population);
//
//        for (int32 ndx = 0; ndx < 20; ndx += 1) {
//            Gait m1 = population[(rand() % 10)];
//            Gait m2 = population[(rand() % 10)];
//            FString child = m1.mate(m2);
//            new_generation.Add(child);
//        }
//        return new_generation;
//    }
//    TArray<FString> sort(TArray<Gait> g) {
//        TArray<FString> new_generation;
//        while (g.Num() > 0) {
//            int32 max = 0;
//            int32 n = 0;
//            for (int ndx = 0; ndx < g.Num(); ndx += 1) {
//                if (max < g[ndx].fitness) {
//                    max = g[ndx].fitness;
//                    n = ndx;
//                }
//            }
//            new_generation.Add(g[n].chromosome);
//            g.RemoveAt(n);
//        }
//        return new_generation;
//    }
//};

UMyBlueprintFunctionLibrary::Simulation::Simulation(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms)
{
    for (int32 i = 0; i < numChroms; i += 1) {
        population.Add(Gait(gen[i], scores[i], lenChroms));
    }
}

TArray<FString> UMyBlueprintFunctionLibrary::run(TArray<FString> gen, TArray<int32> scores, int32 numChroms, int32 lenChroms, bool first)
{
    srand(time(NULL));
    if (first) {
        TArray<FString> population;
        for (int32 ndx = 0; ndx < numChroms; ndx += 1) {
            FString chromosome = "";
            for (int32 i = 0; i < 40; i = i + 1) {
                int32 move = rand() % 16;
                chromosome += MOVES[move];
                chromosome += ",";
            }
            population.Add(chromosome);
        }
        return population;
    }
    else {
        Simulation sim = Simulation(gen, scores, numChroms, lenChroms);
        return sim.cycle(numChroms);
    }
}

TArray<FString> UMyBlueprintFunctionLibrary::Simulation::cycle(int32 numChroms) {
    TArray<FString> new_generation = sort(population);

    for (int32 ndx = 0; ndx < numChroms; ndx += 1) {
        Gait m1 = population[(rand() % (numChroms/2))];
        Gait m2 = population[(rand() % (numChroms/2))];
        FString child = m1.mate(m2);
        new_generation.Add(child);
    }
    return new_generation;
}

TArray<FString> UMyBlueprintFunctionLibrary::Simulation::sort(TArray<Gait> g) {
    TArray<FString> new_generation;
    while (g.Num() > 0) {
        int32 max = 0;
        int32 n = 0;
        for (int ndx = 0; ndx < g.Num(); ndx += 1) {
            if (max < g[ndx].fitness) {
                max = g[ndx].fitness;
                n = ndx;
            }
        }
        new_generation.Add(g[n].chromosome);
        g.RemoveAt(n);
    }
    return new_generation;
}

FString UMyBlueprintFunctionLibrary::Gait::mate(Gait gait2) {
    FString child = "";
    //two point crossover, p is the end of the first section (dna comes from gait 1)
    //from (p,p+q) we take dna from gait 2
    //from(p+q, end) we take dna from gait 1
    int32 p = rand() % length;
    int32 q = p + rand() % (int32)(20 - (length-p));
    //from 0 to p take dna from gait 1 with a 5% chance of mutation
    for (int32 ndx = 0; ndx < p; ndx += 1) {
        float prob = rand() % 20;
        if (prob < 19) {
            child += chromosome[ndx*2];
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
            child += gait2.chromosome[ndx*2];
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
            child += chromosome[ndx*2];
        }
        else {
            child += MOVES[rand() % 16];
        }
        child += ",";
    }
    return child;
}

UMyBlueprintFunctionLibrary::Gait::Gait(FString chrom, int32 score, int32 len) {
    chromosome = chrom;
    fitness = score;
    length = len;
}