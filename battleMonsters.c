//
// Created by luke on 2/9/24.
//

#include "battleMonsters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAbility(battleMonster *monster, Ability *ability){
    if (monster->numAbilities < MAX_ABILITIES){
        monster->abilities[monster->numAbilities] = ability;
        monster->numAbilities++;
    } else {
        printf("Maximum abilities reached. Choose an ability to replace (1-%d), or 0 to cancel:\n", MAX_ABILITIES);
        for (int i = 0; i< MAX_ABILITIES; i++) {
            printf("%d: %s\n", i+1, monster->abilities[i]->name);
        }
        int choice;
        scanf("%d", &choice);
        if (choice > 0 && choice <= MAX_ABILITIES) {
            monster->abilities[choice - 1] = ability;
        } else{
            printf("No abilities replaced.\n");
        }
    }
}
void battleMonsterInitialization(battleMonster *name,int startingHealth, int level, char type[], char monsterName[], int bmSpeed){
    strcpy(name->name, monsterName);
    name->startingHealth = startingHealth;
    name->experience = 0;
    name->level = level;
    name->speed = bmSpeed;
    name->currentHealth = startingHealth;
    strcpy(name->type, type);
    name->numAbilities = 0;
    name->abilities = malloc(MAX_ABILITIES * sizeof(Ability*));
    if (name->abilities == NULL){
        fprintf(stderr, "Failed to allocate memory for abilities \n");
        exit(1);
    }
}