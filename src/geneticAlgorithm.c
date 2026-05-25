#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "oracle.h"

#define POPULATION_SIZE 100

typedef struct Individual {
    char chromosome[9];
    int fitness;
} Individual;

void populate_generation(Individual generation[], char alphabet[]);
void update_generation_fitness_value(Individual generation[]);
int select_parent_index(Individual generation[]);
void breeding_individuals(Individual current_generation[], Individual next_generation[], char alphabet[]);
void crack_password_genetic_algorithm(char alphabet[], char *found_password);

void populate_generation(Individual generation[], char alphabet[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j <  8; j++) {
            int idx = rand() % 62;
            generation[i].chromosome[j] = alphabet[idx];
        }
        generation[i].chromosome[8] = '\0';
        generation[i].fitness = 0;
    }
}

void update_generation_fitness_value(Individual generation[]) {
    int fitness_value;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_value = get_fitness(generation[i].chromosome);
        generation[i].fitness = fitness_value;
    }
}

int select_parent_index(Individual generation[]) {
    int idx1 = rand() % POPULATION_SIZE;
    int idx2 = rand() % POPULATION_SIZE;

    if (generation[idx1].fitness > generation[idx2].fitness) {
        return idx1;
    }
    return idx2;
}

void breeding_individuals(Individual current_generation[], Individual next_generation[], char alphabet[]) {
    for (int i = 0; i < POPULATION_SIZE; i += 2) {
        int parent1_idx = select_parent_index(current_generation);
        int parent2_idx = select_parent_index(current_generation);
        int crossover_point = 1 + (rand() % 7);

        for (int j = 0; j < 8; j++) {
            if (j < crossover_point) {
                next_generation[i].chromosome[j] = current_generation[parent1_idx].chromosome[j];
                if ((rand() % 100) < 5) {next_generation[i].chromosome[j] = alphabet[rand() % 62];};
            } else {
                next_generation[i].chromosome[j] = current_generation[parent2_idx].chromosome[j];
                if ((rand() % 100) < 5) {next_generation[i].chromosome[j] = alphabet[rand() % 62];};
            }
        }
        next_generation[i].chromosome[8] = '\0';

        for (int j = 0; j < 8; j++) {
            if (j < crossover_point) {
                next_generation[i + 1].chromosome[j] = current_generation[parent2_idx].chromosome[j];
                if ((rand() % 100) < 5) {next_generation[i + 1].chromosome[j] = alphabet[rand() % 62];};
            } else {
                next_generation[i + 1].chromosome[j] = current_generation[parent1_idx].chromosome[j];
                if ((rand() % 100) < 5) {next_generation[i + 1].chromosome[j] = alphabet[rand() % 62];};
            }
        }
        next_generation[i + 1].chromosome[8] = '\0';
    }
}

void crack_password_genetic_algorithm(char alphabet[], char *found_password) {
    Individual generation_parent[POPULATION_SIZE];
    Individual generation_children[POPULATION_SIZE];

    Individual *curr_gen = generation_parent;
    Individual *next_gen = generation_children;

    populate_generation(curr_gen, alphabet);
    update_generation_fitness_value(curr_gen);

    while (1) {
        breeding_individuals(curr_gen, next_gen, alphabet);
        update_generation_fitness_value(next_gen);

        Individual *temp = curr_gen;
        curr_gen = next_gen;
        next_gen = temp;

        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (next_gen[i].fitness == 8) {
                strcpy(found_password, next_gen[i].chromosome);
                return;
            }
        }
    }
    return;
}
