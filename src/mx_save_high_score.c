#include "endgame.h"

/*
 * Compare the current score with the high score and save if it is a new record.
 * Logs information or errors using the TraceLog utility.
 */
void mx_save_high_score(const char *name, int score)
{
    int current_best;
    FILE *file;

    current_best = mx_get_high_score();
    if (score <= current_best)
    {
        TraceLog(LOG_INFO, "SAVE: Score %d is not a new record.", score);
        return;
    }

    file = fopen("resource/highscore.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "%s %d\n", name, score);
        fclose(file);
    }
    else
    {
        TraceLog(LOG_ERROR, "SAVE: Could not open file for writing!");
    }
}
