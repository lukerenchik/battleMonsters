//
// Created by Luke on 1/10/2024.
//
#ifndef UNTITLED_BATTLESEQUENCE_H
#define UNTITLED_BATTLESEQUENCE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "battleMonsters.h"
#include "player.h"






int opponentsTurnFlag;
int battleActive;
char playerInput;
char battleType;



void endBattle(battleMonster *userMonster, battleMonster *oppMonster, Player *user){
    if(userMonster->currentHealth == 0){
        printf("%s has ran out of health, you have lost the battle and must return to safety to restore strength\n", userMonster->name);
    }
    if(oppMonster->currentHealth == 0){
        printf("%s has been defeated!\n", oppMonster->name);
        getLoot(oppMonster, user);
    }
    battleActive = 0;
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){

    }
}


void runFromBattle(char bType, battleMonster *userMonster, battleMonster *oppMonster, Player *user){
    if(bType == 'w'){
        char delay;
        printf("Battle Escaped, press any key to continue\n");
        delay = getchar();
        endBattle(userMonster, oppMonster, user);
    }   else{
        printf("Cannot run from player battles.\n\n");
    }
}

void calculateDamage(battleMonster *attacker, battleMonster *defender, Ability *selectedAbility){
    double rand_double = 0.85 + (double)rand() / RAND_MAX * 0.3;
    double abilityDamage = selectedAbility->power * rand_double;
    abilityDamage = round(abilityDamage);
    printf("%s has used %s. It dealt %d damage!\n\n", attacker->name, selectedAbility->name, (int)abilityDamage);
    defender->currentHealth -= (int) abilityDamage;
    if (defender->currentHealth < 0){
        defender->currentHealth = 0;}
    char delay = getchar();
}

void selectAbility (battleMonster *userMonster, battleMonster *oppMonster){
    if(userMonster->currentHealth != 0){
        printf("Select an ability:\n");
        for (int i = 0; i < userMonster->numAbilities; i++){
            printf("%d: %s\n", i + 1, userMonster->abilities[i]->name);
        }

        int choice;
        printf("Enter your choice (1 to %d):", userMonster->numAbilities);
        scanf("%d", &choice);


        //validate choice
        if (choice < 1 || choice > userMonster->numAbilities){
            printf("Invalid Choice. Please select a valid ability. \n");

        }
        else{
            Ability *chosenAbility = userMonster->abilities[choice - 1];
            calculateDamage(userMonster, oppMonster, chosenAbility);
            opponentsTurnFlag = 1;
        }
    }
}

void opponentAbilitySelect(battleMonster *oppMonster, battleMonster *playerMonster) {

    if (oppMonster->currentHealth != 0) {
        int randNum = rand() % 100;
        if (randNum < 50) {
            Ability *selectedAbility = oppMonster->abilities[0];
            calculateDamage(oppMonster, playerMonster, selectedAbility);
            opponentsTurnFlag = 0;
        }else if (randNum < 80) {
            Ability *selectedAbility = oppMonster->abilities[1];
            calculateDamage(oppMonster, playerMonster, selectedAbility);
            opponentsTurnFlag = 0;
        }   else {
            Ability *selectedAbility = oppMonster->abilities[2];
            calculateDamage(oppMonster, playerMonster, selectedAbility);
            opponentsTurnFlag = 0;
        }
    }
}

void printBattleState(battleMonster *userMonster, battleMonster *oppMonster){
    printf("%s: (%d / %d) | %s: (%d / %d)\n",
           userMonster->name,
           userMonster->currentHealth,
           userMonster->startingHealth,
           oppMonster->name,
           oppMonster->currentHealth,
           oppMonster->startingHealth);
}


void startBattle(ActionContext* context, Player* player){

    printf("This is a battle between %s and %s, FIGHT!\n", context->playerMonster->name, context->oppMonster->name);
    battleActive = 1;
    if (context->playerMonster->speed >= context->oppMonster->speed){
        opponentsTurnFlag = 0;
    }
    else{
        opponentsTurnFlag = 1;
    }

    while(battleActive){
        if (opponentsTurnFlag == 1){
            opponentAbilitySelect(context->oppMonster, context->playerMonster);
        }
        printBattleState(context->playerMonster, context->oppMonster);

        if (!battleActive) {
            break;
        }

        if(context->playerMonster->currentHealth <= 0 || context->oppMonster->currentHealth <= 0){
            endBattle(context->playerMonster, context->oppMonster, player);
            break;
        }

        printf("Enter your command: F for Fight, I for Items, R for Run\n");


        playerInput = getchar();

        switch(playerInput) {
            case 'R':
            case 'r':
                runFromBattle(battleType, context->playerMonster, context->oppMonster, player);
                clearInputBuffer();
                break;
            case 'F':
            case 'f':
                selectAbility(context->playerMonster, context->oppMonster);
                clearInputBuffer();
                break;
            case 'I':
            case 'i':
                selectInventoryItem(player, context->playerMonster);
                clearInputBuffer();
                break;
            default:
                break;

        }
    }
}

#endif //UNTITLED_BATTLESEQUENCE_H