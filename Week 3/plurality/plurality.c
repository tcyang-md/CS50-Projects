#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    // iterates through all candidates in array
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate name matches user input (name)
        if (strcmp(name, candidates[i].name) == 0)
        {
            // inc. count
            candidates[i].votes += 1;
            return true;
        }
    }

    // no match
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO

    int highest_vote = 0;
    int tie_marker = 0;

    // iterate through all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // mark down the highest vote count
        if (candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
            // new largest vote so no more tie
            tie_marker = 0;
        }
        // if tie, inc tie marker by 1
        else if (candidates[i].votes == highest_vote)
        {
            tie_marker++;
        }
    }

    // iterate through all candidates again to print out everyone that hit max votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}