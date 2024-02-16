#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Iniatializing custom functions
float count_letters(string text);
float count_words(string text);
float count_sentences(string text);
float coleman(float l, float w, float s);

// Alphabet symbols associated to Scrabble
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z'};
//Detecting the length of the array
int arr_len = sizeof(LETTERS) / sizeof(LETTERS[0]);


int main(void)
{
    string text = get_string("Text: ");
    int col = (int) coleman(count_letters(text), count_words(text), count_sentences(text));
    if (col > 16)
    {
        printf("Grade 16+\n");
    }
    else if (col < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", col);
    }
}

//To calculate the amount of letters
float count_letters(string text)
{
    int letters, i, j, n;
    for (i = 0, letters = 0, n = strlen(text); i < n; i++)
    {
        for (j = 0; j < arr_len; j++)
        {
            if (toupper(text[i]) == LETTERS[j])
            {
                letters++;
            }
        }
    }
    return letters;
}

//To calculate the amount of words (separated by spaces and counting the last
//word when counter reach the last character)
float count_words(string text)
{
    int words, i, n;
    for (i = 0, words = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    if (n == i && n > 0)
    {
        words++;
    }
    return words;
}

//To calculate sentences by dividing the text in its
//(., !, ?)
float count_sentences(string text)
{
    int sent, i, n;
    for (i = 0, sent = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sent++;
        }
    }
    return sent++;
}

//To calculate Coleman's formula considering
//results of operations with data types
float coleman(float l, float w, float s)
{
    float col = round(0.0588 * ((l / w) * 100.0) - 0.296 * ((s / w) * 100.0) - 15.8);
    return col;
}