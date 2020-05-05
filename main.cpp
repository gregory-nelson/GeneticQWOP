#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
 
using namespace std;

const char MOVES[17] = "abcdefghijklmnop";
struct Gait {
    int fitness = 0;
    int length = 20;
    string chromosome;

    Gait(){
        for (int i = 0; i < length; i = i + 1) {
                int move = rand() % 16;
                chromosome += MOVES[move];
            }
            fitness = evaluate();
            cout << chromosome << "\n";
    }

    Gait(string chrom){
    
        chromosome = chrom;
        fitness = evaluate();
    }
    int evaluate(){
        //execute in game run
        return rand() % 100;
    }

    Gait mate(Gait gait2){
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
    
        }
    return Gait(child);
    }

  
};

  bool compareFit (Gait g1, Gait g2) {
    return g1.fitness < g2.fitness;
  }


struct Simulation{
    vector<Gait> population;
    Simulation(){
        for (int i = 0; i < 40; i+=1){
            population.push_back(Gait());
        }
    }
    vector<Gait> cycle(){
         sort(population.begin(), population.end(), compareFit);
        vector<Gait> new_generation;

        for (int ndx = 0; ndx < 20; ndx +=1){
            Gait m1 = population[(rand() % 10)];
            Gait m2 = population[(rand() % 10)];
            Gait child = m1.mate(m2);
            new_generation.push_back(child);
        }
        return new_generation;

    }
    Gait execute(int numCycles){
        for(int c = 0; c<numCycles; c+=1){
            population = cycle();
        }
        sort(population.begin(), population.end(), compareFit);
        return population[0];
    }

};

int main(){
    srand (time(NULL));
    Simulation sim = Simulation();
    cout << (sim.execute(20).fitness);
    return 0;
 }
