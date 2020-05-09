#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;
const char MOVES[17] = "pdcjbihnagfmelko";
struct Gait {
    int fitness = 0;
    int length = 20;
    string chromosome;
    Gait(string chrom, int score){
        chromosome = chrom;
        fitness = score;
    }
    string mate(Gait gait2){
        string child = "";
        //two point crossover, p is the end of the first section (dna comes from gait 1)
        //from (p,p+q) we take dna from gait 2
        //from(p+q, end) we take dna from gait 1
        int p = rand() % 19;
        int q = p + rand() % (int)(20-p);
        //from 0 to p take dna from gait 1 with a 5% chance of mutation
        for(int ndx = 0; ndx < p; ndx+=1){
        float prob = rand() % 20;
            if (prob < 19){
                child += chromosome[ndx];
            }
            else {
                child +=  MOVES[rand() % 16];
            }
            child +=",";
        }
        //from p to p+q take dna from gait 2 with a 5% chance of mutation
        for(int ndx = p; ndx < q; ndx+=1){
            float prob = rand() % 20;
            if (prob < 19){
                child += gait2.chromosome[ndx];
            }
            else {
                child +=  MOVES[rand() % 16];
            }
            child +=",";
        }
        //from p+q to the end take dna from gait 1 with a 5% chance of mutation
        for(int ndx = q; ndx < 20; ndx+=1){
            float prob = rand() % 20;
            if (p < 19){
                child += chromosome[ndx];
            }
            else {
                child +=  MOVES[rand() % 16];
            }
            child +=",";
        }
    return child;
    }
};
bool compareFit (Gait g1, Gait g2) {
    return g1.fitness < g2.fitness;
}
struct Simulation{
    vector<Gait> population;
      Simulation(TArray<string> gen, vector<int> scores, int numChroms){
        for (int i = 0; i < numChroms; i+=1){
            population.push_back(Gait(gen[i], scores[i]));
        }
      }
    TArray<string> cycle(){
        sort(population.begin(), population.end(), compareFit);
        TArray<string> new_generation;

        for (int ndx = 0; ndx < 20; ndx +=1){
            Gait m1 = population[(rand() % 10)];
            Gait m2 = population[(rand() % 10)];
            string child = m1.mate(m2);
            new_generation.Add(child);
        }
        return new_generation;
    }
};

TArray<string> run(TArray<string> gen, vector<int> scores, int numChroms, bool first){
    srand (time(NULL));
    if(first){
      TArray<string> population;
      for(int ndx = 0; ndx < numChroms; ndx+=1){
        string chromosome = "";
        for (int i = 0; i < 40; i = i + 1) {
              int move = rand() % 16;
              chromosome += MOVES[move];
              chromosome +=",";
          }
          population.Add(chromosome);
        }
        return population;
    }
    else{
      Simulation sim = Simulation(gen, scores, numChroms);
      return sim.cycle();
    }
}
