cmake_minimum_required(VERSION 3.27)
project(BattleMonsters C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled STATIC old/library.c
        battleSequence.c
        battleSequence.h
        overWorld.h
        overWorld.c
        introductionSequence.c
        player.c
        player.h
        saveload.c
        saveload.h
        mapData.c
        mapData.h
        battleMonsters.c
        battleMonsters.h
        NPC.c
        NPC.h
        Items.c
        Items.h
        Sound.c
        Sound.h
)

# Uncomment and adjust if you have include directories to add
#include_directories(your/include/directory)

# Uncomment and adjust if you need to link with external libraries
#target_link_libraries(untitled your_external_library)
