#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s wavefile.wav\n", argv[0]);
        return EXIT_FAILURE;
    }
    PlaySound(argv[1], NULL, SND_SYNC | SND_FILENAME);
    return EXIT_SUCCESS;
}