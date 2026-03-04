#include "endgame.h"

/*
 * Retrieve the top player's name and score from the high score file.
 * Defaults to "No Name" and 0 if the file is missing or corrupted.
 */
void mx_get_high_score_entry(char *name, int name_size, int *score)
{
    FILE *file = fopen("resource/highscore.txt", "r");

    *score = 0;
    strncpy(name, "No Name", name_size);
    if (file != NULL)
    {
        if (fscanf(file, "%31s %d", name, score) != 2)
        {
            rewind(file);
            if (fscanf(file, "%d", score) != 1)
                *score = 0;
        }
        fclose(file);
    }
}

/*
 * Fetch the highest score currently recorded in the system.
 * This is a wrapper for mx_get_high_score_entry for simplicity.
 */
int mx_get_high_score(void)
{
    char name[32];
    int score;

    mx_get_high_score_entry(name, sizeof(name), &score);
    return score;
}
