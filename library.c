#include "library.h"
#include <string.h>
#include <stdio.h>

#define MAX_X 15
#define MAX_Y 15

typedef struct {
    int health;
    int experience;
    int level;
    char type[50];

}battleMonster;

typedef struct {
    int xPosition;
    int yPosition;

}mapPerson;


void battleMonsterInitialization(battleMonster *name,int startingHealth, int level, char type[] ){
    name->health = startingHealth;
    name->experience = 0;
    name->level = level;
    strcpy(name->type, type);
}

void mapPersonInitialization(mapPerson *name, int xPos, int yPos){
    name->xPosition = xPos;
    name->yPosition = yPos;
}

void placeOnGrid(mapPerson *name, int grid[MAX_X][MAX_Y]){
    if (name->xPosition >= 0 && name->xPosition < MAX_X && name->yPosition >= 0 && name->yPosition < MAX_Y){
        grid[name->xPosition][name->yPosition] = 1;
    }   else {
        printf("Object position is out of grid bounds.\n");
    }
}

void displayGrid(int grid[MAX_X][MAX_Y]) {
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

void displayGridPointerMath(int arrayPointer, int arrayLength){
    for (int i = 0; i < arrayLength; i++){
        printf("%d ", arrayPointer);
        arrayPointer++;
    }
    printf("\n");
}

int main() {
    battleMonster Aqualix, Zorax;
    mapPerson player, rival;

    //Initializing battleMonsters
    battleMonsterInitialization(&Aqualix, 30, 1, "Water");
    battleMonsterInitialization(&Zorax, 25, 1, "Cosmic");

    //Initializing mapPersons
    mapPersonInitialization(&player, 5, 5);
    mapPersonInitialization(&rival, 10, 10);

    //Creating the map
    int grid[MAX_X][MAX_Y] = {0};
    int *arrayPointer = grid;
    int mapLength = sizeof(grid) / sizeof(grid[0]);

    placeOnGrid(&player, grid);
    placeOnGrid(&rival, grid);

    displayGrid(grid);
    displayGridPointerMath(*arrayPointer, mapLength);
    return 0;

}



