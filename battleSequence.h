//
// Created by Luke on 1/10/2024.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>


#ifndef UNTITLED_BATTLESEQUENCE_H
#define UNTITLED_BATTLESEQUENCE_H
#endif //UNTITLED_BATTLESEQUENCE_H

#define MAX_ABILITIES 4
#define MAX_INVENTORY_SIZE 50

int opponentsTurnFlag;
int battleActive;
char playerInput;
char battleType;

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

typedef void (*ItemFunction)(battleMonster *);

typedef struct {
    char name[50];
    char description[500];
    ItemFunction useFunction;
}Item;

typedef struct {
    Item item;
    unsigned int quantity;
} InventorySlot;

typedef struct {
    InventorySlot inventory[MAX_INVENTORY_SIZE];
    int inventorySize;
    int money;
    int id;
}Player;

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
    battleActive = 0;
}

//End of Items

void addItemToInventory(Player *player, Item newItem, int quantity){
    for (int i = 0; i < player->inventorySize; i++){
        if (strcmp(player->inventory[i].item.name, newItem.name) == 0){
            player->inventory[i].quantity += quantity;
            return;
        }
    }
    //If new item, add to inventory and increase inventory size.
    if (player->inventorySize < MAX_INVENTORY_SIZE){
        player->inventory[player->inventorySize].item = newItem;
        player->inventory[player->inventorySize].quantity = quantity;
        player->inventorySize++;
    }
}

void printInventory(const Player *player){
    if (player == NULL){
        printf("Player data is not available.\n");
        return;
    }
    printf("Players Inventory:\n");
    for (int i = 0; i < player->inventorySize; ++i){
        printf("(%d) %s - %s (Quantity: %d)\n",
               i+1,
               player->inventory[i].item.name,
               player->inventory[i].item.description,
               player->inventory[i].quantity);

    }
}

void selectInventoryItem(Player *player, battleMonster *userMonster) {
    if (player == NULL || player->inventorySize == 0) {
        printf("No items to select.\n");
    } else {
        printInventory(player);
        printf("Select an item number to use, or 'q' to quit: \n");

        char input[10];
        char *result;
        result = fgets(input, sizeof(input), stdin);
        //printf("%s", result);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0;
            if (input[0] == 'q' || input[0] == 'Q') {
                printf("Exiting Item Menu\n");
            } else {
                int choice = atoi(input);
                if (choice > 0 && choice <= player->inventorySize) {
                    if(player->inventory[choice - 1].quantity > 0){
                        player->inventory[choice - 1].item.useFunction(userMonster);
                        player->inventory[choice - 1].quantity -= 1;
                        printf("You have %d %s's remaining.\n", player->inventory[choice-1].quantity,player->inventory[choice-1].item.name);
                    }
                    else{
                        printf("You do not have any %ss.", player->inventory[choice-1].item.name);
                    }
                }
            }
        }
    }
}
void getLoot(battleMonster *oppMonster, Player *user){
    int money = rand() % 10;
    money += 1;
    int multiplier = oppMonster->level;
    int moneyToPlayer = money*multiplier;
    user->money += moneyToPlayer;
    printf("Congratulations you have gained %d munny! You have a total of %d munny.", moneyToPlayer, user->money);

}

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

void initPlayer(Player *player, int invSize, int initMoney){
    player->inventorySize = invSize;
    player->money = initMoney;
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


void startBattle(char bType, battleMonster *userMonster, battleMonster *oppMonster, Player *player){

    printf("This is a battle between %s and %s, FIGHT!\n", userMonster->name, oppMonster->name);
    battleActive = 1;
    if (userMonster->speed >= oppMonster->speed){
        opponentsTurnFlag = 0;
    }
    else{
        opponentsTurnFlag = 1;
    }

    while(battleActive){
        if (opponentsTurnFlag == 1){
            opponentAbilitySelect(oppMonster, userMonster);
        }
        printBattleState(userMonster, oppMonster);

        if (!battleActive) {
            break;
        }

        if(userMonster->currentHealth <= 0 || oppMonster->currentHealth <= 0){
            endBattle(userMonster, oppMonster, player);
            break;
        }

        printf("Enter your command: F for Fight, I for Items, R for Run\n");


        playerInput = getchar();

        switch(playerInput) {
            case 'R':
            case 'r':
                runFromBattle(battleType, userMonster, oppMonster, player);
                clearInputBuffer();
                break;
            case 'F':
            case 'f':
                selectAbility(userMonster, oppMonster);
                clearInputBuffer();
                break;
            case 'I':
            case 'i':
                selectInventoryItem(player, userMonster);
                clearInputBuffer();
                break;
            default:
                break;

        }
    }
}

