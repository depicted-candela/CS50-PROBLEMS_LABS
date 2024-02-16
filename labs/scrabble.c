#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
// Alphabet symbols associated to Scrabble
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compares both of the scores by player
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    // Tie
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    //Length of POINTS array
    int arr_len = sizeof(POINTS) / sizeof(POINTS[0]);
    //Defining variables
    int score, i, n, j;
    //Loop that restart the score to 0 and put as many cycles as the length of the provided string
    for (i = 0, n = strlen(word), score = 0; i < n; i++)
    {
        for (j = 0; j < arr_len; j++)
        {
            //Compares the character from the loop
            //with all of the characters of the alphabet
            //in the array LETTERS and puts the score
            //by mapping the position that satisfies the
            //condition with the same position from the
            //POINTS array
            if (LETTERS[j] == toupper(word[i]))
            {
                score += POINTS[j];
            }
        }
    }
    return score;
}
