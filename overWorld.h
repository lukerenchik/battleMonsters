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

void clearConsole() {
    system("clear");
}

void mapPersonInitializationWithAction(mapPerson *name, int xPos, int yPos, char text[], int ID, battleMonster* equippedBM){
    name->xPosition = xPos;
    name->yPosition = yPos;
    name->ID = ID;
    strcpy(name->actionText, text);
    map[name->xPosition][name->yPosition] = name;
    name->equipped_battle_monster = equippedBM;
}

void addActionToMapPerson(mapPerson *name, ActionFunctionWithContext action, ActionContext* context) {
    name->actionFunction = action;
    name->context = context;
}

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

void clearFromMap(mapPerson *name, mapPerson* grid[MAX_X][MAX_Y]){
    grid[name->xPosition][name->yPosition] = NULL;
}

void mapPersonMovement(mapPerson *person, mapPerson* grid[MAX_X][MAX_Y], char direction) {
    int newX = person->xPosition;
    int newY = person->yPosition;

    switch(direction) {
        case 'U': newY--; break;
        case 'L': newX--; break;
        case 'R': newX++; break;
        case 'D': newY++; break;
        default:
            printf("Invalid direction\n");
            return;
    }

    // Check for boundaries
    if (newX < 0 || newX >= MAX_X || newY < 0 || newY >= MAX_Y) {
        printf("Out of bounds, movement not allowed.\n");
        return;
    }

    // Check for collision
    if (grid[newX][newY] != NULL && grid[newX][newY]->ID != person->ID) {
        printf("Collision detected, movement not allowed.\n");
        return;
    }

    // Update the map and person's position
    grid[person->xPosition][person->yPosition] = NULL; // Clear old position
    person->xPosition = newX;
    person->yPosition = newY;
    grid[newX][newY] = person; // Set new position
}


void placeOnMap(mapPerson *name, mapPerson* grid[MAX_X][MAX_Y]) {
    if (name->xPosition >= 0 && name->xPosition < MAX_X && name->yPosition >= 0 && name->yPosition < MAX_Y) {
        grid[name->xPosition][name->yPosition] = name;
    } else {
        printf("Object position is out of grid bounds.\n");
    }
}

void displayMapFull(mapPerson* grid[MAX_X][MAX_Y]) {
    char buffer[MAX_X * 2 + 1]; // Buffer for each row (+1 for null terminator)

    for (int y = 0; y < MAX_Y; y++) {
        int bufIndex = 0;
        for (int x = 0; x < MAX_X; x++) {
            if (grid[x][y] != NULL) {
                buffer[bufIndex++] = 'X';  // Object present at this cell
            } else {
                buffer[bufIndex++] = '.';  // Empty cell
            }
            buffer[bufIndex++] = ' '; // Space between cells
        }
        buffer[bufIndex] = '\0'; // Null-terminate the string
        printf("%s\n", buffer);  // Print the entire row at once
    }
}


void displayMapAroundPlayer(mapPerson* grid[MAX_X][MAX_Y], int playerX, int playerY) {
    //Clear Previous Map
    clearConsole();

    int displayWidth = 24;
    int displayHeight = 6;

    // Calculate the starting and ending points for x and y
    int startX = playerX - displayWidth / 2;
    int startY = playerY - displayHeight / 2;
    int endX = playerX + displayWidth / 2;
    int endY = playerY + displayHeight / 2;

    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > MAX_X) endX = MAX_X;
    if (endY > MAX_Y) endY = MAX_Y;


    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            if (grid[x][y] != NULL) {
                printf("X ");  // Object present at this cell
            } else {
                printf(". ");  // Empty cell
            }
        }
        printf("\n");  // New line at the end of each row
    }
}

mapPerson* isActionAdjacent(mapPerson* grid[MAX_X][MAX_Y], mapPerson *person) {
    int directions[8][2] = {
            {-1, -1}, {0, -1}, {1, -1},
            {-1,  0},          {1,  0},
            {-1,  1}, {0,  1}, {1,  1}
    };

    for (int i = 0; i < 8; i++) {
        int dx = person->xPosition + directions[i][0];
        int dy = person->yPosition + directions[i][1];

        if (dx >= 0 && dx < MAX_X && dy >= 0 && dy < MAX_Y) {
            if (grid[dx][dy] != NULL && grid[dx][dy] != person) { // Check if the cell is occupied by another mapPerson
                return grid[dx][dy];
            }
        }
    }
    return NULL;
}

#endif //UNTITLED_BATTLEMONSTERSREFORMATTED_H