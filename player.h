//
// Created by luke on 2/9/24.

#ifndef


#include "Items.h"
#include "battleMonster.h"

#define MAX_INVENTORY_SIZE 50


#define PLAYER_H

typedef struct {
    Item item;
    unsigned int quantity;
} InventorySlot;

typedef struct {
    InventorySlot inventory[MAX_INVENTORY_SIZE];
    battleMonster* battle_monster;
    int inventorySize;
    int money;
    int id;
}Player;

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

void initPlayer(Player *player, int invSize, int initMoney){
    player->inventorySize = invSize;
    player->money = initMoney;
}

void assignBattleMonsterToPlayer(Player* player, battleMonster* battleMonster) {
    player->battle_monster = battleMonster;
}

battleMonster* getPlayerBattleMonster(Player* player) {
    return player->battle_monster;
}

#endif //PLAYER_H
