//
// Created by luke on 2/9/24.
//
#include "Items.h"

#include <stdio.h>

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