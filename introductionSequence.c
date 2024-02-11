#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *introductionText = "Welcome to the world of Monstrum Chronicles, a place remarkably similar to our Earth but with one extraordinary difference: the coexistence of humans and enigmatic creatures known as 'Monstrums.' This world, brimming with vibrant ecosystems, is home to diverse cultures, bustling cities, and tranquil towns. Among these towns is the quaint and picturesque Pinegrove, nestled between the whispering forests and the serene Bluecap Mountains. In Pinegrove, life moves at a gentle pace. Here, you step into the shoes of Alex, a young and aspiring Monstrum Tamer. Raised by a single parent, Alex has grown up alongside these mystical creatures, learning to understand and train them under the watchful eye of their mentor, Casey. Casey, a retired Monstrum Tamer, runs a small training ground on the outskirts of town, known affectionately to locals as 'The Nook.'\n"
                               "\n"
                               "Pinegrove, despite its small size, is a melting pot of cultures due to the rare Monstrums that inhabit the surrounding wilds. People from all over the world visit Pinegrove, bringing with them stories and customs, making it a vibrant hub for Monstrum Tamers.\n"
                               "\n"
                               "Alex's life, though humble, is filled with adventure. Days are spent exploring the dense forests, identifying and studying different Monstrum species, and training with them in The Nook. Evenings are for returning to the heart of Pinegrove, where the community gathers to share tales and enjoy the local delicacies of the town's quaint cafes and eateries.\n"
                               "\n"
                               "The bond between Alex and their Monstrums is special. Each Monstrum, from the swift-footed Sprintail to the majestic Skywhale, shares a unique relationship with Alex, full of trust and mutual respect. This bond is the cornerstone of Alex's training methods, which emphasize understanding and empathy over dominance.\n"
                               "\n"
                               "In Pinegrove, every face is familiar, and every day is a new opportunity to grow closer to the Monstrums and understand their mysterious world. Little does Alex know, their simple life is about to take a dramatic turn with the arrival of a mysterious envelope, postmarked with a seal never seen before in Pinegrove. This envelope holds a secret that will catapult Alex from the comfort of their small-town life into an adventure beyond their wildest dreams."; // Your long string


void displayTextInChunks(const char *text, int chunkSize) {
    int length = strlen(text);
    int start = 0;

    while (start < length) {
        // Calculate end position of the current chunk
        int end = start + chunkSize;
        if (end > length) {
            end = length;
        } else {
            // Adjust end position to avoid splitting a word
            while (end > start && text[end] != ' ' && text[end] != '\n') {
                end--;
            }
            if (end == start) {
                end = start + chunkSize; // In case of very long words
            }
        }

        // Print the current chunk
        for (int i = start; i < end; i++) {
            putchar(text[i]);
        }

        // Wait for user input
        printf("\n...");
        while (1) {
            int c = getchar();
            if (c == '\n' || c == ' ') break;
        }

        // Move to the next chunk
        start = end;
    }
}
