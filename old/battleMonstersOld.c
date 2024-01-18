//
// Created by Luke on 12/22/2023.
//

//TODO 1.) Create a scanning function that looks around the player to see if there are nearby NPCs, once npc is found display their action text.
#include "library.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_X 100
#define MAX_Y 100

//Creating the map


typedef struct {
    int health;
    int experience;
    int level;
    char type[50];

}battleMonster;

typedef struct {
    int xPosition;
    int yPosition;
    char actionText[200];
    int ID;
}mapPerson;

mapPerson* map[MAX_X][MAX_Y] = {0};


void battleMonsterInitialization(battleMonster *name,int startingHealth, int level, char type[] ){
    name->health = startingHealth;
    name->experience = 0;
    name->level = level;
    strcpy(name->type, type);
}

void mapPersonInitialization(mapPerson *name, int xPos, int yPos, char text[], int ID){
    name->xPosition = xPos;
    name->yPosition = yPos;
    name->ID = ID;
    strcpy(name->actionText, text);
    map[name->xPosition][name->yPosition] = name;
}


void clearFromMap(mapPerson *name, int grid[MAX_X][MAX_Y]){
    grid[name->xPosition][name->yPosition] = 0;
}

void mapPersonMovement(mapPerson *name, int yPos, int xPos, char direction) {
    int newXPos = xPos;
    int newYPos = yPos;

    switch(direction) {
        case 'U':
           newYPos = yPos - 1;
            break;
        case 'L':
            newXPos = xPos - 1;
            break;
        case 'R':
            newXPos = xPos + 1;
            break;
        case 'D':
            newYPos = yPos + 1;
            break;
        default:
            return; // Invalid direction, so no movement
    }

    // Check for boundaries and collision
    if (newXPos >= 0 && newXPos < MAX_X && newYPos >= 0 && newYPos < MAX_Y  && map[newXPos][newYPos]!= 2) {
        // Update position only if there's no collision and within boundaries
        name->xPosition = newXPos;
        name->yPosition = newYPos;
    } else {
        // Handle collision or out of bounds
        printf("Collision detected or out of bounds, movement not allowed.\n");
    }
}



void placeOnMap(mapPerson *name, mapPerson* grid[MAX_X][MAX_Y]) {
    if (name->xPosition >= 0 && name->xPosition < MAX_X && name->yPosition >= 0 && name->yPosition < MAX_Y) {
        grid[name->xPosition][name->yPosition] = 1;
    } else {
        printf("Object position is out of grid bounds.\n");
    }
}


void displayMapFull(int grid[MAX_X][MAX_Y]) {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (grid[x][y] == 1) {
                printf("X ");  // Object present at this cell
            } else {
                printf(". ");  // Empty cell
            }
        }
        printf("\n");  // New line at the end of each row
    }
}

void displayMapAroundPlayer(int grid[MAX_X][MAX_Y], int playerX, int playerY) {
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
            if (grid[x][y] == 1) {
                printf("X ");  // Object present at this cell
            } else {
                printf(". ");  // Empty cell
            }
        }
        printf("\n");  // New line at the end of each row
    }
}

void displayGridPointerMath(int arrayPointer, int arrayLength){
    for (int i = 0; i < arrayLength; i++){
        printf("%d ", arrayPointer);
        arrayPointer++;
    }
    printf("\n");
}

void npcAction(mapPerson *name) {
    printf("%s\n", name->actionText);
}

bool isActionAdjacent(int grid[MAX_X][MAX_Y], int yPos, int xPos) {
    //Directions relative to the current position
    int directions[8][2] = {
            {-1, -1}, // Top-left
            {-1, 0},  // Top
            {-1, 1},  // Top-right
            {0, -1},  // Left
            {0, 1},   // Right
            {1, -1},  // Bottom-left
            {1, 0},   // Bottom
            {1, 1}    // Bottom-right
    };

    for (int i = 0; i < 8; i++){
        int dy = yPos + directions[i][1];
        int dx = xPos + directions[i][0];

        //Check boundaries
        if (dx >= 0 && dx < MAX_X && dy >= 0 && dy < MAX_Y) {
            if (grid[dx][dy] == 1) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    battleMonster Aqualix, Zorax;
    mapPerson player, rival;
    char playerInput;

    //Initializing battleMonsters
    battleMonsterInitialization(&Aqualix, 30, 1, "Water");
    battleMonsterInitialization(&Zorax, 25, 1, "Cosmic");

    //Initializing mapPersons
    mapPersonInitialization(&player, 6, 3, "", 0);
    mapPersonInitialization(&rival, 18, 3, "Well, well, look who finally showed up! Ready to taste defeat?", 1);



    placeOnMap(&player, map);
    placeOnMap(&rival, map);

    displayMapAroundPlayer(map, player.xPosition, player.yPosition);
    //displayMapFull(map);


    while (1) {
        playerInput = getchar();

        if (playerInput == 'q' || playerInput == 'Q'){
            break;
        }

        switch(playerInput){
            case 'w':
            case 'W':
                clearFromMap(&player, map);
                mapPersonMovement(&player, player.yPosition, player.xPosition, 'U');
                break;
            case 'A':
            case 'a':
                clearFromMap(&player, map);
                mapPersonMovement(&player, player.yPosition, player.xPosition, 'L');
                break;
            case 'S':
            case 's':
                clearFromMap(&player, map);
                mapPersonMovement(&player, player.yPosition, player.xPosition, 'D');
                break;
            case 'D':
            case 'd':
                clearFromMap(&player, map);
                mapPersonMovement(&player, player.yPosition, player.xPosition, 'R');
                break;
            case 'E':
            case 'e':
                if (isActionAdjacent(map, player.xPosition,player.yPosition)){

                }
            default:
                break;

        }

        placeOnMap(&player, map, 'h');
        displayMapAroundPlayer(map, player.xPosition, player.yPosition);
        while (getchar() != '\n');
    }


    return 0;

}

