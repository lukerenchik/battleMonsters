//
// Created by luke on 2/9/24.
//

#ifndef BATTLEMONSTER_H
#define BATTLEMONSTER_H

#define MAX_ABILITIES 4

typedef struct {
    char name[50];
    char type[50];
    int power;
}Ability;

typedef struct {
    char name[50];
    int startingHealth;
    int currentHealth;
    int totalWins;
    int totalLosses;
    int experience;
    int level;
    char type[50];
    Ability** abilities;
    int numAbilities;
    int speed;
}battleMonster;

void addAbility(battleMonster *monster, Ability *ability);
void battleMonsterInitialization(battleMonster *name,int startingHealth, int level, char type[], char monsterName[], int bmSpeed);

#endif //BATTLEMONSTER_H
