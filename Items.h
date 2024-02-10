//
// Created by luke on 2/9/24.
//

#ifndef ITEMS_H
#define ITEMS_H

typedef void (*ItemFunction)(battleMonster *);

typedef struct {
    char name[50];
    char description[500];
    ItemFunction useFunction;
}Item;

//Items

void useHealthPotion(battleMonster *monster){
    monster->currentHealth += 25;
    if(monster->currentHealth > monster->startingHealth){
        monster->currentHealth = monster->startingHealth;
    }
    printf("%s has been healed for 25 hitpoints!\n", monster->name);
}

void useSuperHealthPotion(battleMonster *monster){
    monster->currentHealth += 50;
    if(monster->currentHealth > monster->startingHealth) {
        monster->currentHealth = monster->startingHealth;
    }
    printf("%s has been healed for 50 hitpoints!\n", monster->name);
}


void useSmokeBomb(battleMonster *monster){
    printf("You throw down a smoke bomb and quickly escape from the engagement. ");
    //TODO: Reimplement Escape Battle Functionality.
}

//End of Items


//End of Item



#endif //ITEMS_H
