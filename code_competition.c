#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 10
#define MAX_NAME_LEN 50


int main()
{
    char sentence[100];
    char names[MAX_PLAYERS][MAX_NAME_LEN];
    double timeTaken[MAX_PLAYERS];
    float accuracy[MAX_PLAYERS];
    float wpm[MAX_PLAYERS];
    char typed[200];
    int i, j, n;

    printf(" \n-x-x-x-x-x-x-x Typing Speed Tester -x-x-x-x-x-x-x \n\n");
    printf("Enter the sentence you want to test with:\n");
    fgets(sentence, sizeof(sentence), stdin);
    for (i = 0; sentence[i] != '\0'; i++)//remove newline
    {
        if (sentence[i] == '\n') 
        {
            sentence[i] = '\0';
            break;
        }
    }
    printf("\nEnter number of players (max %d): ", MAX_PLAYERS);
    scanf("%d", &n);
    getchar(); // clear newline

    if (n < 1 || n > MAX_PLAYERS) 
    {
        printf("Invalid number of players!\n");
        return 0;
    }

    printf("\nSentence to type:\n\"%s\"\n\n", sentence);

    // For each player until limit
    for (i = 0; i < n; i++) 
    {
        int correct = 0, words = 1;
        time_t start, end;

        printf("\nPlayer %d, enter your name: ", i + 1);
        fgets(names[i], sizeof(names[i]), stdin);
        names[i][strcspn(names[i], "\n")] = '\0'; // remove newline

        printf("\n%s, Press ENTER when ready to start...", names[i]);
        getchar();

        printf("\nType the sentence below:\n\"%s\"\n\n", sentence);

        // Start timer
        start = time(NULL);

        fgets(typed, sizeof(typed), stdin);
        typed[strcspn(typed, "\n")] = '\0'; // remove newline

        // End timer
        end = time(NULL);
        timeTaken[i] = difftime(end, start);

        // Count correct chars
        for (j = 0; sentence[j] != '\0' && typed[j] != '\0'; j++) 
        {
            if (sentence[j] == typed[j])
            correct++;
        }

        // Count words
        for (j = 0; typed[j] != '\0'; j++) 
        {
            if (typed[j] == ' ' && typed[j + 1] != ' ' && typed[j + 1] != '\0')
            words++;
        }

        // Calculate stats
        accuracy[i] = ((float)correct / j) * 100;
        wpm[i] = (words / timeTaken[i]) * 60;

        printf("\n------- %s's Results:---------\n", names[i]);
        printf("Time Taken : %.2f sec\n", timeTaken[i]);
        printf("Words Typed: %d\n", words);
        printf("Speed      : %.2f WPM\n", wpm[i]);
        printf("Accuracy   : %.2f%%\n", accuracy[i]);
        printf("---------------------------------------\n");
    }

    // Leaderboard (sort by WPM)
    for (i = 0; i < n - 1; i++) 
    {
        for (j = i + 1; j < n; j++) 
        {
            if (wpm[j] > wpm[i]) 
            {
                float tempW = wpm[i];
                wpm[i] = wpm[j];
                wpm[j] = tempW;

                float tempA = accuracy[i];
                accuracy[i] = accuracy[j];
                accuracy[j] = tempA;

                double tempT = timeTaken[i];
                timeTaken[i] = timeTaken[j];
                timeTaken[j] = tempT;

                char tempN[MAX_NAME_LEN];
                strcpy(tempN, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempN);
            }
        }
    }

    printf("\n============ FINAL LEADERBOARD =============\n");
    printf("%-15s %-10s %-10s %-10s\n", "Name", "WPM", "Accuracy", "Time(s)");
    printf("------------------------------------------\n");
    for (i = 0; i < n; i++) 
    {
        printf("%-15s %-10.2f %-10.2f %-10.2f\n",
        names[i], wpm[i], accuracy[i], timeTaken[i]);
    }
    printf("============================================\n");

    printf("\n-x-x-x-x-x-x-x %s wins with %.2f WPM! -x-x-x-x-x-x-x\n\n", names[0], wpm[0]);

    return 0;
}
