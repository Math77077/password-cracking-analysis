#ifndef ORACLE_H
#define ORACLE_H

#include <stdbool.h>

#define MODE_RAMDOM 0
#define MODE_FILE 1

void oracle_init(int mode, const char* path);
bool check_full(const char* attempt);
bool check_partial(const char* part, int start_pos);
int get_fitness(const char* attempt);
long long get_oracle_hits();

#endif