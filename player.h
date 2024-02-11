//
// Created by luke on 2/9/24.

#ifndef PLAYER_H
#define PLAYER_H

#include "Items.h"
#include "battleMonsters.h"

#define MAX_INVENTORY_SIZE 50

typedef struct Player Player;

typedef struct{
    char param;
    battleMonster* playerMonster;
    battleMonster* oppMonster;
    struct Player* player;
} ActionContext;

typedef void (*ActionFunctionWithContext)(ActionContext*, Player*);

typedef struct {
    Item item;
    unsigned int quantity;
} InventorySlot;

typedef struct {
    int xPosition;
    int yPosition;
    char actionText[200];
    int ID;
    battleMonster* equipped_battle_monster;
    ActionFunctionWithContext actionFunction;
    ActionContext* context;
}mapPerson;

struct Player {
    mapPerson location;
    InventorySlot inventory[MAX_INVENTORY_SIZE];
    battleMonster* equipped_battle_monster;
    int inventorySize;
    int money;
    int id;
};

void addItemToInventory(Player *player, Item newItem, int quantity);
void printInventory(const Player *player);
void selectInventoryItem(Player *player, battleMonster *userMonster);
void initPlayer(Player *player, int invSize, int initMoney, int x, int y);
void assignBattleMonsterToPlayer(Player* player, battleMonster* battleMonster);
battleMonster* getPlayerBattleMonster(Player* player);
void assignActionContext(ActionContext* ac, char param, battleMonster* playerBM, battleMonster* oppBM, Player* player);
void getLoot(battleMonster *oppMonster, Player *user);

#endif //PLAYER_H
