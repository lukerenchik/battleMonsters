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

extern int opponentsTurnFlag;
extern int battleActive;
extern char playerInput;
extern char battleType;

void endBattle(battleMonster *userMonster, battleMonster *oppMonster, Player *user);
void clearInputBuffer();
void runFromBattle(char bType, battleMonster *userMonster, battleMonster *oppMonster, Player *user);
void calculateDamage(battleMonster *attacker, battleMonster *defender, Ability *selectedAbility);
void selectAbility (battleMonster *userMonster, battleMonster *oppMonster);
void opponentAbilitySelect(battleMonster *oppMonster, battleMonster *playerMonster);
void printBattleState(battleMonster *userMonster, battleMonster *oppMonster);
void startBattle(ActionContext* context, Player* player);

#endif //UNTITLED_BATTLESEQUENCE_H