//
// Created by Luke on 12/26/2023.
//
#include "overWorld.h"
#include "battleSequence.h"

int main() {
    mapPerson player, rival;

    //Initializing mapPersons
    mapPersonInitialization(&player, 6, 3, "", 0);
    mapPersonInitializationWithAction(&rival, 18, 3, "Well, well, look who finally showed up! Ready to taste defeat?", 1,startBattle('p',));

    placeOnMap(&player, map);
    placeOnMap(&rival, map);

    displayMapAroundPlayer(map, player.xPosition, player.yPosition);

    bool needsRedraw = true;

    while (1) {
        if (needsRedraw) {
            displayMapAroundPlayer(map, player.xPosition, player.yPosition);
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
                mapPersonMovement(&player, map, 'U');
                moved = true;
                break;
            case 'A':
            case 'a':
                mapPersonMovement(&player, map, 'L');
                moved = true;
                break;
            case 'S':
            case 's':
                mapPersonMovement(&player, map, 'D');
                moved = true;
                break;
            case 'D':
            case 'd':
                mapPersonMovement(&player, map, 'R');
                moved = true;
                break;
            case 'E':
            case 'e': {
                moved = false;
                mapPerson* adjacentPerson = isActionAdjacent(map, &player);
                if (adjacentPerson != NULL) {
                    clearConsole();
                    displayMapAroundPlayer(map, player.xPosition, player.yPosition);
                    printf("%s\n", adjacentPerson->actionText); // Print the actionText of the adjacent mapPerson
                } else {
                    clearConsole();
                    displayMapAroundPlayer(map, player.xPosition, player.yPosition);
                    printf("No one is nearby.\n");
                }
                break;
            }
            default:
                break;

        }
            if (moved) {
                placeOnMap(&player, map);
                needsRedraw = true;
            }
    }

    return 0;
}
