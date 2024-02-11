//
// Created by luke on 2/9/24.
//

#ifndef ITEMS_H
#define ITEMS_H
#include "battleMonsters.h"

typedef void (*ItemFunction)(battleMonster *);

typedef struct {
    char name[50];
    char description[500];
    ItemFunction useFunction;
}Item;


void useHealthPotion(battleMonster *monster);
void useSuperHealthPotion(battleMonster *monster);
void useSmokeBomb(battleMonster *monster);


#endif //ITEMS_H
