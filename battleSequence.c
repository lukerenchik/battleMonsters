//
// Created by Luke on 1/6/2024.
//

#include "battleSequence.h"

int main() {

    srand(time(NULL));
    battleType = 'p';

    battleMonster Aqualix, Zorax;

    Player User;
    initPlayer(&User,0,0);

    battleMonsterInitialization(&Aqualix, 30, 5, "Water", "Aqualix", 5);
    battleMonsterInitialization(&Zorax, 25, 5, "Cosmic", "Zorax", 3);

    Ability waterSlash = {.name = "Water Slash", .type = "Water", .power = 11};
    Ability wingDrop = {.name = "Wing Drop", .type = "Normal", .power = 9};
    Ability cosmicWind = {.name = "Cosmic Wind", .type = "Cosmic", .power = 14};
    Ability imprison = {.name = "Imprison", .type = "Normal", .power = 7};

    Item healthPotion = {"Health Potion", "Heals the users Battle Monster by 25 points.",
                          useHealthPotion};
    Item bigHealthPotion = {"Big Health Potion", "Heals the users Battle Monster by 50 points.",
                             useSuperHealthPotion};
    Item smokeBomb = {"Smoke Bomb", "Immediately Escapes Battle", useSmokeBomb};



    addItemToInventory(&User, healthPotion, 3);
    addItemToInventory(&User, bigHealthPotion, 1);
    addItemToInventory(&User, smokeBomb, 2);

    addAbility(&Aqualix, &waterSlash);
    addAbility(&Aqualix, &wingDrop);
    addAbility(&Zorax, &wingDrop);
    addAbility(&Zorax, &imprison);
    addAbility(&Zorax, &cosmicWind);


    startBattle(battleType, &Aqualix, &Zorax, &User);
}