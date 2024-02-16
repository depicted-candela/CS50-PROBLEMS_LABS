#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void bubble(candidate ca[], int c);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
            break;
        }
        else
        {
            continue;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO

    bubble(candidates, candidate_count);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[i + 1].votes)
        {
            printf("%s\n", candidates[i].name);
            continue;
        }
        else
        {
            printf("%s\n", candidates[i].name);
            break;
        }
    }
    return;
}

void bubble(candidate ca[], int c)
{
    string name;
    int votes;

    if (c < 2)
    {
        return;
    }

    for (int ss = 0; ss < c - 1; ss++)
    {
        if (candidates[ss].votes < candidates[ss + 1].votes)
        {
            name = ca[ss].name;
            votes = ca[ss].votes;
            ca[ss].name = ca[ss + 1].name;
            ca[ss].votes = ca[ss + 1].votes;
            ca[ss + 1].name = name;
            ca[ss + 1].votes = votes;
        }
    }
    c--;
    bubble(ca, c);
}

