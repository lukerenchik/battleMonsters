//
// Created by Luke on 1/10/2024.
//

#ifndef UNTITLED_BATTLEMONSTERSREFORMATTED_H
#define UNTITLED_BATTLEMONSTERSREFORMATTED_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "battleSequence.h"

#define MAX_X 100
#define MAX_Y 100

mapPerson* map[MAX_X][MAX_Y] = {0};

void clearConsole();
void mapPersonInitializationWithAction(mapPerson *name, int xPos, int yPos, char text[], int ID, battleMonster* equippedBM);
void addActionToMapPerson(mapPerson *name, ActionFunctionWithContext action, ActionContext* context);
void clearFromMap(mapPerson *name, mapPerson* grid[MAX_X][MAX_Y]);
void mapPersonMovement(mapPerson *person, mapPerson* grid[MAX_X][MAX_Y], char direction);
void placeOnMap(mapPerson *name, mapPerson* grid[MAX_X][MAX_Y]);
void displayMapFull(mapPerson* grid[MAX_X][MAX_Y]);
void displayMapAroundPlayer(mapPerson* grid[MAX_X][MAX_Y], int playerX, int playerY);
mapPerson* isActionAdjacent(mapPerson* grid[MAX_X][MAX_Y], mapPerson *person);


#endif //UNTITLED_BATTLEMONSTERSREFORMATTED_H


/*
 *  Uneeded With Embedding mapPerson in Player Struct
 *
 *
void mapPersonInitialization(mapPerson *name, int xPos, int yPos, char text[], int ID){
    name->xPosition = xPos;
    name->yPosition = yPos;
    name->ID = ID;
    strcpy(name->actionText, text);
    map[name->xPosition][name->yPosition] = name;
}
*/