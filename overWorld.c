//
// Created by Luke on 12/26/2023.
//
#include "overWorld.h"
#include "battleSequence.h"
#include <stdbool.h>

int main() {
    mapPerson rival;
    Player player;

    battleMonster Aqualix, Zorax;

    battleMonsterInitialization(&Aqualix, 30, 5, "Water", "Aqualix", 5);
    battleMonsterInitialization(&Zorax, 25, 5, "Cosmic", "Zorax", 3);

    Ability waterSlash = {.name = "Water Slash", .type = "Water", .power = 11};
    Ability wingDrop = {.name = "Wing Drop", .type = "Normal", .power = 9};
    Ability cosmicWind = {.name = "Cosmic Wind", .type = "Cosmic", .power = 14};
    Ability imprison = {.name = "Imprison", .type = "Normal", .power = 7};

    addAbility(&Aqualix, &waterSlash);
    addAbility(&Aqualix, &wingDrop);
    addAbility(&Zorax, &wingDrop);
    addAbility(&Zorax, &imprison);
    addAbility(&Zorax, &cosmicWind);

    Item healthPotion = {"Health Potion", "Heals the users Battle Monster by 25 points.",
                      useHealthPotion};
    Item bigHealthPotion = {"Big Health Potion", "Heals the users Battle Monster by 50 points.",
                             useSuperHealthPotion};
    Item smokeBomb = {"Smoke Bomb", "Immediately Escapes Battle", useSmokeBomb};



    addItemToInventory(&player, healthPotion, 3);
    addItemToInventory(&player, bigHealthPotion, 1);
    addItemToInventory(&player, smokeBomb, 2);


    //Initializing mapPersons
    initPlayer(&player, 10, 25, 3, 3);
    assignBattleMonsterToPlayer(&player, &Aqualix);

    mapPersonInitializationWithAction(&rival, 18, 3, "Well, well, look who finally showed up! Ready to taste defeat?", 1, &Zorax);

    ActionContext rivalContext;
    assignActionContext(&rivalContext, 'p', player.equipped_battle_monster, rival.equipped_battle_monster, &player);

    addActionToMapPerson(&rival, startBattle, &rivalContext);

    placeOnMap(&player.location, map);
    placeOnMap(&rival, map);

    displayMapAroundPlayer(map, player.location.xPosition, player.location.yPosition);

    bool needsRedraw = true;

    while (1) {
        if (needsRedraw) {
            displayMapAroundPlayer(map, player.location.xPosition, player.location.yPosition);
            needsRedraw = false;
        }

        playerInput = getchar();

            if (playerInput == 'q' || playerInput == 'Q'){
                break;
            }

            bool moved = false;

        switch(playerInput){
            case 'w':
            case 'W':
                mapPersonMovement(&player.location, map, 'U');
                moved = true;
                break;
            case 'A':
            case 'a':
                mapPersonMovement(&player.location, map, 'L');
                moved = true;
                break;
            case 'S':
            case 's':
                mapPersonMovement(&player.location, map, 'D');
                moved = true;
                break;
            case 'D':
            case 'd':
                mapPersonMovement(&player.location, map, 'R');
                moved = true;
                break;
            case 'E':
            case 'e': {
                moved = false;
                mapPerson* adjacentPerson = isActionAdjacent(map, &player.location);
                if (adjacentPerson != NULL) {
                    clearConsole();
                    displayMapAroundPlayer(map, player.location.xPosition, player.location.yPosition);
                    printf("%s\n", adjacentPerson->actionText); // Print the actionText of the adjacent mapPerson
                    if(adjacentPerson->actionFunction) {
                        adjacentPerson->actionFunction(adjacentPerson->context, &player);
                    }
                } else {
                    clearConsole();
                    displayMapAroundPlayer(map, player.location.xPosition, player.location.yPosition);
                    printf("No one is nearby.\n");
                }
                break;
            }
            default:
                break;

        }
            if (moved) {
                placeOnMap(&player.location, map);
                needsRedraw = true;
            }
    }

    return 0;
}
