cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_library(untitled STATIC old/library.c
        battleSequence.c
        battleSequence.h
        overWorld.c
        overWorld.h
        overWorld.c
        introductionSequence.c
        introductionSequence.c
        player.c
        player.h
        saveload.c
        saveload.h
        mapData.c
        mapData.h
        battleMonsters.c
        battleMonster.h
        NPC.c
        NPC.h
        Items.c
        Items.h
        Sound.c
        Sound.h
)
